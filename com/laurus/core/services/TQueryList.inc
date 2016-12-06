<?php
/**
 * Description of TQueryList
 * @todo Need to remove direct dependancy of the ModuleLoader
 * @author kunal.mestri
 */
class TQueryList {
    /**
     *
     * @var <TQueryList>
     */
    private static $staticInstance;
    private $queryList;
    protected static $logger;
    private function  __construct() {
       self::$logger=Logger::getLogger(__CLASS__);
       $this->queryList=json_decode(file_get_contents($_SERVER["QUERYLIST_FILE"]),true);
       if(class_exists(ModuleLoader)){
            $this->getExternalQueries();
       }
    }
    public function getQuery($str,$moduleName=null){
        if($moduleName==null){
            self::$logger->info($this->queryList[$str]);
            return $this->queryList[$str];
        }else {
            self::$logger->info($this->queryList[$moduleName][$str]);
            return $this->queryList[$moduleName][$str];
        }
    }
    public static function getInstance(){
        if(self::$staticInstance==null){
            self::$staticInstance=new TQueryList();
        }
        return self::$staticInstance;
    } 
    
    protected function readExternalQueries($filePath){
        if(file_exists($filePath)){
            self::$logger->debug("TQuery List for module found");
            $newQueryList=json_decode(file_get_contents($filePath),true);
            if($newQueryList!=null){
                if(empty($this->queryList)){
                    $this->queryList=$newQueryList;
                }else{
                    $this->queryList=array_merge($this->queryList,$newQueryList);
                }
                self::$logger->debug("Query List Updated");
                //self::$logger->info($this->queryList);
            }
        }
        
    }
    
    public function getExternalQueries(){
        self::$logger->debug(__METHOD__);
        $list=  ModuleLoader::getInstance()->getAllModules();
        self::$logger->debug($list);
        for ($i=0 ; $i < $list->size() ; $i++ ) { 
            /* @var $module SMVCModule*/
            $module= $list->get($i);
            if($module->getTqueryListFilePath()!=null)
                $this->readExternalQueries($module->getTqueryListFilePath());
        }
    }   
}
?>
