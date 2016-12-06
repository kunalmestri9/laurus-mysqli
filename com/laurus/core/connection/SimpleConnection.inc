<?php

import('com.laurus.core.connection.IConnectionNormal');
import('com.laurus.core.sql.SqlException');

/**
 * @name SimpleConnection
 * @author Kunal Mestri
 * 
 */
Class SimpleConnection implements IConnectionNormal {

    private $con;
    protected $logger;

    public function close() {
        return mysql_close($this->con);
    }

    public function __construct() {
        $this->logger = Logger::getLogger(__CLASS__);
    }

    public function connect(/* String */ $hostname, /* String */ $username, /* String */ $password, /* String */ $db, $new_link = false) {
        $this->logger->info("Connecting to DB");
        $this->logger->debug($hostname . "@" . $username);
        $this->con = mysqli_connect($hostname, $username, $password,$db);

        mysqli_query($this->con,"SET NAMES 'utf8'");
        if (!$this->con) {
            $this->logger->error("Counld not connect to database server");
            throw new SqlException("Counld not connect to database server", mysqli_connect_errno());
        }
        if(!mysqli_select_db($this->con,$db)){
            $this->logger->error("Cannot connect to database : " .$db);
            throw new SqlException("Could not connect to database", mysqli_errno($this->con));
        }
        $this->logger->debug("Successfully Connected to '" . $db . "'");
        return $this->con;
    }

}

?>
