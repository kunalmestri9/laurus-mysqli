<?php
import('com.laurus.core.connection.IConnectionProperties');
import('com.laurus.core.connection.SimpleConnection');
import('com.laurus.core.connection.ExtendedConnection');
import('com.laurus.core.connection.IConnectionType');
import('com.laurus.core.resultset.ResultSet');
import('com.laurus.core.statement.Statement');
import('com.laurus.core.statement.MultiInsertStatement');
import('com.laurus.core.sql.SqlException');


/**
 * @name CoreConnection
 * @author Amruta Vichare
 */

class  CoreConnection {
    protected $incon;
    protected $type;
    /**
     * @var <SimpleConnection>
     */
    protected $simpleConnection=null;
    protected $extendedConnection=null;
    protected $logger;

    public function  __construct() {
        $this->logger=Logger::getLogger(__CLASS__);
    }
    
    public function getConnection() {
        return $this->incon;
    }
    public function setConnectionType($type){
        $this->type=$type;
        if($type==IConnectionType::SIMPLECONNECTION){
           return $this->createSimpleConnection();
        }
        else if($type==IConnectionType::EXTENDEDCONNECTION){
           return $this->createExtendedConnection();
        }
    }

    protected function createExtendedConnection(){
        $this->extendedConnection=new ExtendedConnection();
        $this->incon=$this->extendedConnection->connect(IConnectionProperties::getDbServer(), IConnectionProperties::getDbUserName(), IConnectionProperties::getDbPassword(),IConnectionProperties::getDbName());
        return $this->extendedConnection;
    }
    protected function createSimpleConnection(){
        $this->simpleConnection=new SimpleConnection();
        $this->incon=$this->simpleConnection->connect(IConnectionProperties::getDbServer(), IConnectionProperties::getDbUserName(), IConnectionProperties::getDbPassword(),IConnectionProperties::getDbName());
        return $this->simpleConnection;
    }

    public function getExtendedConnection(){
        return $this->extendedConnection;
    }
    public function getSimpleConnection(){
        return $this->simpleConnection;
    }
    
    public function createStatement(){
        $stmt=new Statement();
        $stmt->setConn($this->getConnection());
        return $stmt;
    }


    public function close(){
        if( $this->type== IConnectionType::SIMPLECONNECTION)
            return  $this->simpleConnection->close();
        else if($this->type== IConnectionType::EXTENDEDCONNECTION)
            return  $this->extendedConnection->close();
    }
    public function execute(IStatement $stmt){
       if($stmt->getQuery()==null){
           $this->logger->error("WTF!!Query is null");
           throw new Exception("CORECONNECTION::execute-Query is null");
       }
       $this->logger->debug($stmt->getQuery());
       $stmt->setStmt(mysqli_query($this->getConnection(), $stmt->getQuery()));
       $this->logger->debug($stmt->getStmt());
       return new Resultset($stmt->getStmt());
    }
    public function executeUpdate(IStatement $stmt,$isIdNeedShouldBeReturn=false){
       if($stmt->getQuery()==null){
           $this->logger->error("WTF!!Query is null");
           throw new Exception("CORECONNECTION::execute-Query is null");
       }
       $this->logger->debug($stmt->getQuery());
        $stmt->setStmt(mysqli_query($this->getConnection(), $stmt->getQuery()));
       $result= $stmt->getStmt();
       if(!$result){
           $this->logger->error("Some Exception while executeUpdate :: ". mysqli_error($this->getConnection()));
           throw new SqlException("Execute Update failed",  mysqli_errno($this->getConnection()));
       }
       if(mysqli_affected_rows($this->getConnection())==0){
           throw new SqlException("Zero rows afected",SQLExceptionType::NO_ROWS_AFFECTED);
       }
       if($isIdNeedShouldBeReturn)return mysqli_insert_id($this->getConnection());
       return $result;
    }
}




?>
