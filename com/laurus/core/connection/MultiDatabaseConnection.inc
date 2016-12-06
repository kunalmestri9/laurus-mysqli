<?php
/**
 * Description of MultiDatabaseConnection
 *
 * @author Bhupesh
 */
import('com.laurus.core.connection.CoreConnection');
class MultiDatabaseConnection extends CoreConnection{
    protected $logger;
    private static $CONFIG_FILE= "dbconfig.json";
    private static $CFG_FOLDERNAME="cfg";
    private $arr;
    private $databseLocator;
    public function __construct() {
        $this->logger=Logger::getLogger(__CLASS__);
        $this->arr=$this->readConfigurationFile();
    }
    protected function createExtendedConnection($confName) {
        $this->simpleConnection=new ExtendedConnection();
        $this->incon=$this->extendedConnection->connect($this->arr[$confName]["DATABASE_SERVER"], $this->arr[$confName]["DATABASE_USER"],$this->arr[$confName]["DATABASE_PASSWORD"],$this->arr[$confName]["DATABASE_NAME"]);
        return $this->extendedConnection;
    }
    protected function createSimpleConnection($confName) {
        $this->simpleConnection=new SimpleConnection();
        $this->incon=$this->simpleConnection->connect($this->arr[$confName]["DATABASE_SERVER"], $this->arr[$confName]["DATABASE_USER"],$this->arr[$confName]["DATABASE_PASSWORD"],$this->arr[$confName]["DATABASE_NAME"],$this->arr[$confName]["NEW_LINK"]);
        return $this->simpleConnection;
    }
    public function setConnectionType($type){
        $this->type=$type;
        if($type==IConnectionType::SIMPLECONNECTION){
           return $this->createSimpleConnection($this->databseLocator);
        }
        else if($type==IConnectionType::EXTENDEDCONNECTION){
           return $this->createExtendedConnection($this->databseLocator);
        }
    }
    public function setDatabaseLocator($dbconf){
        $this->databseLocator=$dbconf;
    }
    private function readConfigurationFile(){
        $pageConfigFileName=$this->getFilePath();
        if(file_exists($pageConfigFileName)){
            $arr=json_decode(file_get_contents($this->getFilePath()),true);
        }else{
            self::$logger->warn($pageConfigFileName ."dbconfig.json not found in the application");
        }
        return $arr;
    }
    private function getFilePath(){
        return  $_SERVER["APPLICATION_PATH"] . DIRECTORY_SEPARATOR . self::$CFG_FOLDERNAME  . DIRECTORY_SEPARATOR . self::$CONFIG_FILE;
    }   
}
?>