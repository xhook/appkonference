<?php
function getConference($db,$conference) {
	include('config.php.inc');
	$members = array();
	if ($db_engine == "sqlite") {
		$sql = "select member_id from online where conference='$conference' order by talking desc";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			array_push($members,$row['member_id']);
		}
	} else if ($db_engine == "mysql") {
		$sql = "select member_id from online where conference='$conference' order by talking desc";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while (($row = mysql_fetch_array($query))) {
			array_push($members,$row['member_id']);
		}
	}
	return $members;
}

function getAllConferences($db) {
	include('config.php.inc');
	$conferences = array();
	if ($db_engine == "sqlite") {
		$sql = "select conference from online group by conference";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			array_push($conferences,$row['conference']);
		}
	} else if ($db_engine == "mysql") {
		$sql = "select conference from online group by conference";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while (($row = mysql_fetch_array($query))) {
			array_push($conferences,$row['conference']);
		}
	}
	return $conferences;
}

function getConferenceCount($db,$conference) {
	include('config.php.inc');
	if ($db_engine =="sqlite") {
		$sql = "select count(*) from online where conference='$conference'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return($row['count(*)']);
		}
	} else if ($db_engine =="mysql") {
		$sql = "select count(*) from online where conference='$conference'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while ( ($row = mysql_fetch_array($query))) {
			return($row['count(*)']);
		}
	}
}

function getChannel($db,$member_id) {
	include('config.php.inc');
	if ($db_engine == "sqlite") {
		$sql = "select channel from online where member_id='$member_id'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return $row['channel'];
		}
	} else if ($db_engine == "mysql") {
		$sql = "select channel from online where member_id='$member_id'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while ( ($row = mysql_fetch_array($query))) {
			return $row['channel'];
		}
	}
}

function getScoreid($db,$member_id) {
	include('config.php.inc');
	if ($db_engine == "sqlite") {
		$sql = "select scoreid from online where member_id='$member_id'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return $row['scoreid'];
		}
	} else if ($db_engine == "mysql") {
		$sql = "select scoreid from online where member_id='$member_id'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while ( ($row = mysql_fetch_array($query))) {
			return $row['scoreid'];
		}
	}
}

function getName($db,$member_id) {
	include('config.php.inc');
	if ($db_engine == "sqlite") {
		$sql = "select name from online where member_id='$member_id'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return $row['name'];
		}
	}  else if ($db_engine == "mysql") {
		$sql = "select name from online where member_id='$member_id'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while ( ($row = mysql_fetch_array($query))) {
			return $row['name'];
		}
	}
}

function getNumber($db,$member_id) {
	include('config.php.inc');
	if ($db_engine == "sqlite") {
		$sql = "select number from online where member_id='$member_id'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return $row['number'];
		}
	} else if ($db_engine == "mysql") {
		$sql = "select number from online where member_id='$member_id'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while (($row = mysql_fetch_array($query))) {
			return $row['number'];
		}
	}
}

function getTalking($db,$member_id) {
	include('config.php.inc');
	if ($db_engine =="sqlite") {
		$sql = "select talking from online where member_id='$member_id'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return $row['talking'];
		}
	} else if ($db_engine == "mysql") {
		$sql = "select talking from online where member_id='$member_id'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while ( ($row = mysql_fetch_array($query))) {
			return $row['talking'];
		}
	}
}

function getMuted($db,$member_id) {
	include('config.php.inc');
	if ($db_engine == "sqlite") {
		$sql = "select muted from online where member_id='$member_id'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		while ( ($row = $results->fetchArray())) {
			return $row['muted'];
		}
	} else if ($db_engine == "mysql") {
		$sql = "select muted from online where member_id='$member_id'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		while ( ($row = mysql_fetch_array($query))) {
			return $row['muted'];
		}
	}
}

function muteConference($conference) {
	if (trim($conference) != "") {
		$fp = managerConnect();
	        $conference = trim($conference);
        	fputs($fp,"Action: Command\r\n");
	        fputs($fp,"Command: konference muteconference $conference\r\n\r\n");
        	fputs($fp,"action: logoff\r\n");
	        fputs($fp,"\r\n");
	}
}

function unmuteConference($conference) {
	if (trim($conference) != "") {
		$fp = managerConnect();
	        $conference = trim($conference);
        	fputs($fp,"Action: Command\r\n");
	        fputs($fp,"Command: konference unmuteconference $conference\r\n\r\n");
        	fputs($fp,"action: logoff\r\n");
	        fputs($fp,"\r\n");
	}
}

function kickUser($conference,$channel) {
	$fp = managerConnect();
        $conference = trim($conference);
       	fputs($fp,"Action: Command\r\n");
        fputs($fp,"Command: konference kickchannel $channel\r\n\r\n");
       	fputs($fp,"action: logoff\r\n");
        fputs($fp,"\r\n");
	//read until the end
        while (!feof($fp)) {
                $line=(fgets($fp, 4096));
                echo "$line<br>";
        }
}

function volumeDown($channel) {
	$fp = managerConnect();
       	fputs($fp,"Action: Command\r\n");
        fputs($fp,"Command: konference talkvolume $channel down\r\n\r\n");
       	fputs($fp,"action: logoff\r\n");
        fputs($fp,"\r\n");
        while (!feof($fp)) {
                $line=(fgets($fp, 4096));
                echo "$line<br>";
        }
}

function volumeUp($channel) {
	$fp = managerConnect();
       	fputs($fp,"Action: Command\r\n");
        fputs($fp,"Command: konference talkvolume $channel up\r\n\r\n");
       	fputs($fp,"action: logoff\r\n");
        fputs($fp,"\r\n");
        while (!feof($fp)) {
                $line=(fgets($fp, 4096));
                echo "$line<br>";
        }
}

function muteUser($db,$channel) {
	include('config.php.inc');
	$fp = managerConnect();
	if ($db_engine == "sqlite") {
		$sql = "select muted from online where channel='$channel'";
		$results = $db->query($sql);
		if (!$results) die (sqlite3_error($db));
		$muted = 0;
		while ( ($row = $results->fetchArray())) {
			$muted = $row['muted'];
		}
	} else if ($db_engine == "mysql") {
		$sql = "select muted from online where channel='$channel'";
		$query = mysql_query($sql,$db) or die (mysql_error());
		$muted = 0;
		while (($row = mysql_fetch_array($query))) {
			$muted = $row['muted'];
		}
	}

	if ($muted == 1) {
	       	fputs($fp,"Action: Command\r\n");
        	fputs($fp,"Command: konference unmutechannel $channel\r\n\r\n");
	       	fputs($fp,"action: logoff\r\n");
        	fputs($fp,"\r\n");
	        while (!feof($fp)) {
        	        $line=(fgets($fp, 4096));
	                echo "$line<br>";
        	}
		changeMute($db,$channel,0);
	} else if ($muted == 0) {
	       	fputs($fp,"Action: Command\r\n");
        	fputs($fp,"Command: konference mutechannel $channel\r\n\r\n");
	       	fputs($fp,"action: logoff\r\n");
        	fputs($fp,"\r\n");
	        while (!feof($fp)) {
        	        $line=(fgets($fp, 4096));
                	echo "$line<br>";
	        }
		changeMute($db,$channel,1);
	}


}

function changeMute($db,$channel,$mute) {
	include('config.php.inc');
	if ($db_engine == "sqlite") {
		$sql = "update online set muted='$mute' where channel='$channel'";
		sqlite3_exec($db, $sql);
	} else if ($db_engine == "mysql") {
		$sql = "update online set muted='$mute' where channel='$channel'";
		mysql_query($sql,$db);
	}
}

function getRecordedConferences() {
	include('config.php.inc');
	$d = dir($recordings_location);
	$dirs = array();
	while (false !== ($entry = $d->read())) {
		if ($entry != "." && $entry != "..") {
			array_push($dirs,$entry);
		}
	}
	return $dirs;
}

function getRecordingsForConference($conference) {
	include('config.php.inc');	
	$files = array();
	if ($handle = opendir($recordings_location . "/" . $conference)) {
		while (false !== ($file = readdir($handle))) {
			if ($file != "." && $file != "..") {
				array_push($files,$file);
			}
		}
	}
	return $files;
}

function recordConference($db,$conference) {
	if (trim($conference) != "") {
		include('config.php.inc');
		$fp = managerConnect();
	        $conference = trim($conference);
		if ($db_engine == "sqlite") {
			$sql = "select channel from online where number='900'";
			$query = sqlite3_query($db, $sql);
			if (!$query) die (sqlite3_error($db));
			$channel = "";
			while ( ($row = sqlite3_fetch_array($query))) {
				$channel = $row['channel'];
			}
		} else if ($db_engine == "mysql") {
			$sql = "select channel from online where number='900'";
			$query = mysql_query($sql,$db) or die (mysql_error());
			$channel = "";
			while ( ($row = mysql_fetch_array($query))) {
				$channel = $row['channel'];
			}
		}
		if ($channel != "") {
	        	fputs($fp,"Action: Command\r\n");
	        	fputs($fp,"Command: konference kickchannel $channel\r\n\r\n");
        		fputs($fp,"action: logoff\r\n");
		        fputs($fp,"\r\n");
		        while (!feof($fp)) {
                		$line=(fgets($fp, 4096));
		                echo "$line<br>";
		        }
		} else {
			$time = time();
		        $RECORDINGFILE=$recordings_location . "/" . $conference . "/" . $time;
		        @mkdir($recordings_location . "/" . $conference,0777);
		        chown($recordings_location, $recordings_username);
		        @touch($RECORDINGFILE . ".wav");
		        chown($RECORDINGFILE . ".wav",$recordings_username);
			$cmd .= "Action: Originate\r\n";
			$cmd .= "Channel: Local/recorder@conference\r\n";
			$cmd .= "MaxRetries: 0\r\n";
			$cmd .= "RetryTime: 15\r\n";
			$cmd .= "WaitTime: 15\r\n";
			$cmd .= "Context: conference\r\n";
			$cmd .= "Exten: enterconf\r\n";
			$cmd .= "Priority: 1\r\n";
			$cmd .= "Callerid: Recorder <900>\r\n";
			$cmd .= "Variable: conference=$conference\r\n";
			$cmd .= "Variable: chown_user=$recordings_username\r\n";
			$cmd .= "Variable: RECORDINGFILE=$RECORDINGFILE\r\n\r\n";
			fputs($fp,$cmd);
                        fputs($fp,"action: logoff\r\n");
                        fputs($fp,"\r\n");
		        while (!feof($fp)) {
                		$line=(fgets($fp, 4096));
		                echo "$line<br>";
		        }	
		}

	}
}



function managerConnect() {
	include('config.php.inc');
        $fp = fsockopen($manager_host, 5038, $errno, $errstr, 20);
        fputs($fp,"Action: login\r\n");
        fputs($fp,"Username: $manager_username\r\n");
        fputs($fp,"Secret: $manager_password\r\n");
        fputs($fp,"Events: off\r\n");
        fputs($fp,"\r\n");
        return $fp;
}

?>
