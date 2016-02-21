<?php
 
require_once 'DB_Functions.php';
$db = new DB_Functions();
 
// json response array
$response = array("error" => FALSE);
 
if (1) {
 
    // receiving the post params
    $fname = $_POST['name'];
    $email = $_POST['email'];
    $password = $_POST['password'];
    $cpassword=$_POST['cpassword'];
    $lname=$_POST['lname'];
    $mobile=$_POST['mobile'];
    $dept=$_POST['dept'];
   /* $fname = "dsddf";
    $email = "dsdfdfd";
    $password ="dssd";
    $cpassword="dsdfdf";
    $lname="dsdfdf";
    $mobile='sdsfsf';
    $dept='dddvd';*/
 
    // check if user is already existed with the same email
    if ($db->isUserExisted($mobile)) {
        // user already existed
        $response["error"] = TRUE;
        $response["error_msg"] = "User already existed with " . $mobile;
        echo json_encode($response);
    } else {
        // create a new user
        $user = $db->storeUser($fname,$lname,$mobile, $email,$dept, $password);
        if ($user) {
            // user stored successfully
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
        } else {
            // user failed to store
            $response["error"] = TRUE;
            $response["error_msg"] = "Unknown error occurred in registration!";
            echo json_encode($response);
        }
    }
} else {
    $response["error"] = TRUE;
    $response["error_msg"] = "Required parameters (name, email or password) is missing!";
    echo json_encode($response);
}
?>