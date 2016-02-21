<?php
require_once 'DB_Functions.php';
$db = new DB_Functions();
 
// json response array
$response = array("error" => FALSE);
 
if (1) {
 
    // receiving the post params
    $mobile = $_POST['mobile'];
    $password = $_POST['password'];
 
    // get the user by email and password
    $user = $db->getUserByEmailAndPassword($mobile, $password);
 
    if ($user != false) {
        // use is found
        $response["error"] = FALSE;
            $response["uid"] = $user["unique_id"];
            $response["user"]["fname"] = $user["fname"];
            $response["user"]["lname"] = $user["lname"];
            $response["user"]["mobile"] = $user["mobile"];
            $response["user"]["dept"] = $user["dept"];
            $response["user"]["email"] = $user["email"];
            $response["user"]["created_at"] = $user["created_at"];
            $response["user"]["updated_at"] = $user["updated_at"];
            echo json_encode($response);
        echo json_encode($response);
    } else {
        // user is not found with the credentials
        $response["error"] = TRUE;
        $response["error_msg"] = "Login credentials are wrong. Please try again!";
        echo json_encode($response);
    }
} else {
    // required post params is missing
    $response["error"] = TRUE;
    $response["error_msg"] = "Required parameters email or password is missing!";
    echo json_encode($response);
}
?>