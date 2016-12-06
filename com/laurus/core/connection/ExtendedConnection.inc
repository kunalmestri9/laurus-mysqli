<?php

import('com.laurus.core.connection.IConnectionExtended');
import('com.laurus.core.sql.SqlException');

/**
 * @name ExtendedConnection
 * @author Kunal Mestri
 */
class ExtendedConnection implements IConnectionExtended {

    private $con;

    public function connect($hostname, $username, $password, $dbname, $new_link = false) {

        $this->con = mysqli_connect($hostname, $username, $password);

        mysqli_select_db($this->con,$dbname);
        return $this->con;
    }

    public function cancelTransation() {
        mysqli_rollback($this->con);
        mysqli_autocommit($this->con,true);
    }

    public function close() {
        return mysqli_close($this->con);
    }

    public function completeTransaction() {
        mysqli_commit($this->con);
        mysqli_autocommit($this->con,true);
    }

    public function startTransaction() {
        mysqli_autocommit($this->con,false);
       
    }

}

?>
