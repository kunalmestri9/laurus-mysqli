<?php
import('com.laurus.core.collection.map.ExceptionEntry');
import('com.laurus.core.collection.map.Map');
class SQLExceptionService {
	public static $ERRORREPO=null;

	public static $RESULTSET_EMPTY=null;
	function __construct(){
		self::$ERRORREPO=new Map();
		self::$ERRORREPO->put(new ExceptionEntry( ISQLExceptionType::RESULTSET_EXCEPTION,"SQL Exception odd type Exception"));
	}
}
?>
