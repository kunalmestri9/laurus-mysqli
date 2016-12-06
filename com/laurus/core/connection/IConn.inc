<?php

/**
 * @name IConn
 * @version 1.0
 * @author Kunal Mestri
 */
interface IConn{
    /**
     *@name connect
     * @param <String> $hostname
     * @param <String> $username
     * @param <String> $password
     * @return <Resource> $conn
     */
    public function connect($hostname,$username,$password,$dbname);


    /**
     * @name close
     *  @return <boolean>
     */
    public function close();
}


?>
