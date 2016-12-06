<?php
class IConnectionProperties{
    public  static function getDbServer(){
        return $_SERVER["DATABASE_SERVER"];
    }
    public  static function getDbUserName(){
        return $_SERVER["DATABASE_USER_NAME"];
    }
    public  static function getDbPassword(){
        return $_SERVER["DATABASE_USER_PASSWORD"];
    }
    public  static function getDbName(){
        return $_SERVER["DATABASE_NAME"];
    }
}
?>
