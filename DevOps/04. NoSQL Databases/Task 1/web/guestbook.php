<?php

error_reporting(E_ALL);
ini_set('display_errors', 1);

if (isset($_GET['cmd']) === true) {
  $host = "mongo-host";
  $connection = new MongoClient( "mongodb://".$host.":27017" );
  $db = $connection->selectDB('test');
  $collection = $db->selectCollection('messages');

  header('Content-Type: application/json');

  if ($_GET['cmd'] == 'set') {

    $collection->insert(array("message" => $_GET['value'], "published" => date("Y-m-d H:i:s")));
    
    print('{"message": "Inserted."}');
  } 
  else {
    $results = $collection->find();

    $value = "";

    foreach($results as $result) {
       $value = $value.$result['message'].",";
    }

    $value = substr($value, 0, -1);
    
    print('{"data": "' . $value . '"}');
  }
} 
else {
  phpinfo();
} ?>
