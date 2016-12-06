<?php
import('com.laurus.core.security.encoders.QueryEncoder');
import('com.laurus.core.statement.IStatement');
import('com.laurus.core.exception.UnsupportedTypeException');
import('com.laurus.core.statement.Statement');
import('com.laurus.core.collection.Statement');


/**
 * Description of MultiInsertStatement
 * 
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
class MultiInsertStatement  extends Statement {
    private $innerQuery;
    private $list;
    
    public function addInternalQuery($str){
        $this->innerQuery=$str;
    }
    public function __construct($conn) {
        $this->conn=$conn;
        $this->list=new SimpleList();
    }
    public function getNewRow(){
        $statement=$this->conn->createStatement();
        $statement->setQuery($this->innerQuery);
        return $statement;
    }
    
    public function addRow(\Statement $stmt){
        $this->list->add($stmt);
    }
    protected function getMergedInnerQuery(){
        $innerQuery="";
        for ($index = 0; $index < $this->list->size() ; $index++) {
            /* @var $stmt Statement */
            $stmt=$this->list->get($index);
            $innerQuery.= $stmt->getQuery();
            if($index!=($this->list->size()-1)){
                $innerQuery.=",";
            }
        }
        return $innerQuery;
    }
    
    public function getQuery(){
        $this->setQueryPart(1, $this->getMergedInnerQuery() );
        return parent::getQuery();
    }
    
            
            
    
}
?>
