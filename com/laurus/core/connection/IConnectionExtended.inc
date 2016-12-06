<?php

import('com.laurus.core.connection.IConn');
/**
 * @name IConnectionExtended
 * implement this interface if you want to Extende connection  simple connection
 * 
 */
interface IConnectionExtended extends IConn{
    public function startTransaction();
    public function completeTransaction();
    public function cancelTransation();
}

?>
