<?php
import('com.laurus.core.security.encoders.QueryEncoder');
import('com.laurus.core.statement.IStatement');
import('com.laurus.core.exception.UnsupportedTypeException');
/**
 * Description of Statement
 * Modified on : 11 Feb 2014 
 * Added new method setQueryPart for adding dyanamic order by or where clauses or other query parts.
 * TODO Validate query paramters
 * 
 * @author Kunal Mestri <kunal@laurus-it.com>
 */
class Statement  implements IStatement {
    private  $query;
    private $stmt;
    private $conn;
    public function getConn() {
        return $this->conn;
    }
    public function setConn($conn) {
        $this->conn = $conn;
    }
            
    public function getStmt() {
        return $this->stmt;
    }

    public function setStmt($stmt) {
        $this->stmt = $stmt;
    }

    public function getQuery(){
        return $this->query;
    }
    public function setQuery($query) {
        $this->query=$this->generatedNewQuery($query);

    }
    private function generatedNewQuery($s){
	$newStr="";
	$arr=str_split($s);
	$count=0;
	foreach($arr as $val){
		$newStr.=$val;
		if($val=="?"){
			$newStr.=++$count ."_";
		}
       }
	return $newStr;
    }
    private function getKKey($num){
        return "?".$num ."_";
    }

    public function setString($key, $val) {
      //echo "<h1>".$this->query."</h1>";
      //echo $this->getKKey($key);
      //if(is_string($val)){
            if(strpos($this->query,$this->getKKey($key) )){
                $encodedval="'".QueryEncoder::encodeString($val,$this->conn)."'";
                $this->query=str_replace($this->getKKey($key),$encodedval,$this->query);
            }
            else
                throw new UnsupportedTypeException(getType($var1),"STRING");

       //}
    }
    
    public function setNonMandatoryString($key, $val) {
            if(!TUtilString::isValidString($val)){
                if(strpos($this->query,$this->getKKey($key) )){
                    $this->query=str_replace($this->getKKey($key),"NULL",$this->query);
                }
                else
                    throw new UnsupportedTypeException(getType($val),"STRING");
            }else{
                $this->setString($key, $val);
            }
    }
    
     public function setDouble($key, $val) {
       if(is_double((double)$val)){
            if(strpos($this->query, $this->getKKey($key))){
                $encodedval=QueryEncoder::encodeInteger($val);
                 $this->query=str_replace($this->getKKey($key),$encodedval,$this->query);
            }
            else
                throw new UnsupportedTypeException(getType($val),"INTEGER");
       }
    }
    public function setInt($key, $val) {
       if(is_int((int)$val)){
            if(strpos($this->query, $this->getKKey($key))){
                $encodedval=QueryEncoder::encodeInteger($val);
                 $this->query=str_replace($this->getKKey($key),$encodedval,$this->query);
            }
            else
                throw new UnsupportedTypeException(getType($val),"INTEGER");
       }
    }
    
    public function setNonMandatoryInt($key, $val) {
            if(!TUtilString::isValidString($val)){
                if(strpos($this->query,$this->getKKey($key) )){
                    $this->query=str_replace($this->getKKey($key),"NULL",$this->query);
                }
                else
                    throw new UnsupportedTypeException(getType($val),"STRING");
            }else{
                $this->setInt($key, $val);
            }
    }
     public function setDate($key, $val) {
      if( is_date($val)){
            if(strpos($this->query, $this->getKKey($key))){
                $encodedval=QueryEncoder::encodeDate($val);
                str_replace($this->getKKey($key),$encodedval,$this->query);
            }
            else
              // throw new UnSupportedTypeException()
                throw new UnsupportedTypeException(getType($var1),"DATE");
       }
    }
    public function setFloat($key, $val) {
      if( is_float($val)){
            if(strpos($this->query, $this->getKKey($key))){
                $encodedval=QueryEncoder::encodeFloat($val);
                str_replace($this->getKKey($key),$encodedval,$this->query);
            }
            else
              // throw new UnSupportedTypeException()
                throw new UnsupportedTypeException(getType($var1),"FLOAT");
       }
    }
    
    public function setTime($key, $val) {
        if(strpos($this->query, $key)){
                $encodedval=QueryEncoder::encodeTime($val);
                str_replace($key,$encodedval,$this->query);
            }
            /*else
               throw new UnSupportedTypeException()*/
       }

     public function setTableName($key, $val) {
      if(is_string($key)){
            if(strpos($this->query, $key)){
                $encodedval=QueryEncoder::encodeString($val);
                 $this->query=str_replace($key,$encodedval,$this->query);

            }
       }
    }
    
    public function setQueryPart($key ,$val){
        if(is_string($val)){
            if(strpos($this->query, $this->getKKey($key)) && $this->validateQueryParameter($val)){
                 $encodedval=QueryEncoder::encodeInteger($val);
                 $this->query=str_replace($this->getKKey($key),$encodedval,$this->query);
            }
        }
    }
    /**
     * TODO Need to create a const array for the expected query parameters and 
     * @param type string
     * @return boolean
     */
    protected function validateQueryParameter($val){
        return true;
    }
}
?>
