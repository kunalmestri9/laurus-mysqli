<?php
class ResultSet{
    private $logger;
    private $result_resource;
    private $cursor;
    private $length;
    private $current_row;
    public function  __construct($res) {
        $this->logger = Logger::getLogger(__CLASS__);
        $this->cursor=0;
        $this->result_resource=$res;
        $this->logger->debug($res);
        $this->logger->debug("mysqli_num_rows");
        $this->logger->debug(mysqli_num_rows($res));
        if($res!=null){
            $this->length=  mysqli_num_rows($res);
           
        }
    }
    public function hasRecords(){
        return ( $this->length > 0 );
    }
    public function length(){
        return mysqli_num_rows($this->result_resource);
    }
    
    public function next(){
        $this->logger->debug($this->length);
        $this->logger->debug($this->cursor);
        if($this->cursor<$this->length){
            $this->cursor++;
            $row=  mysqli_fetch_array($this->result_resource);
            $this->logger->debug($row);
            if(!$row){
                return false;
            }else
                $this->current_row=$row;
            return true;
        }
        return false;
    }
    public function get($index){
        return $this->current_row[$index];
    }

}
?>
