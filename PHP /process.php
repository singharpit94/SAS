<?php
	//Generic php function to send GCM push notification
   function sendPushNotificationToGCM($registation_ids, $message) {
		//Google cloud messaging GCM-API url
        $url = 'https://android.googleapis.com/gcm/send';
        $fields = array(
            'registration_ids' => $registation_ids,
            'data' => $message,
        );
		// Update your Google Cloud Messaging API Key
		if (!defined('GOOGLE_API_KEY')) {
			define("GOOGLE_API_KEY", "AIzaSyC8p3FPIIavnBAyBpIwscFh3LCWcppZk9g"); 		
		}
        $headers = array(
            'Authorization: key=' . GOOGLE_API_KEY,
            'Content-Type: application/json'
        );
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_POST, true);
        curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt ($ch, CURLOPT_SSL_VERIFYHOST, 0);	
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($fields));
        $result = curl_exec($ch);				
        if ($result === FALSE) {
            die('Curl failed: ' . curl_error($ch));
        }
        curl_close($ch);
        return $result;
    }
?>
<?php
 $con = mysqli_connect("127.0.0.1","root","arpit1234");
      if (!$con)
  {
    die('Could not connect: ' . mysqli_error());
  }

  mysqli_select_db($con,"mess");
  $selUsers = $_POST['sendmsg'];
  if(empty($selUsers)) 
  {
    echo("You didn't select any users.");
  } 
  else
  {	
	//$resp = "<tr id='header'><td>GCM Response [".date("h:i:sa")."]</td></tr>";
    $userCount = count($selUsers);
	
	$greetMsg = $_POST['message'];
	$respJson = '{"greetMsg":"'.$greetMsg.'"}';
	$registation_ids = array();
	for($i=0; $i < $userCount; $i++)
    {
      $d=$selUsers[$i];
      $query="SELECT * FROM gcmusers WHERE email='$d'";
      if ($result=mysqli_query($con,$query))
  {
  
  
       
	    
		$row = mysqli_fetch_assoc($result);		
		//Add RegIds retrieved from DB to $registration_ids
   // echo $row['uuid'];
    $a=$row['email'];
   // $d=$selUsers[0];
    $resp = "<tr id='header'><td>".$row['uuid']. "[".date("h:i:sa")."]</td></tr>";
		array_push($registation_ids, $row['uuid']);				  
    } 
  }
	// JSON Msg to be transmitted to selected Users
	$message = array("m" => $respJson);  
	$pushsts = sendPushNotificationToGCM($registation_ids, $message); 
	$resp = $resp."<tr><td>".$pushsts."</td></tr>";
	echo "<table>".$resp."</table>";
  }
	
?>