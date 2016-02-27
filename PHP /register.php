<?php
    $con = mysqli_connect("127.0.0.1","root","arpit1234");
    $username = $_POST['username'];
	$name = $_POST['name'];
	$email = $_POST['email'];
	$password = $_POST['password'];
        $uuid= $_POST['uuid'];

	

	if (!$con)
	{
		die('Could not connect: ' . mysqli_error());
	}

	mysqli_select_db($con,"mess");
	$sql = "SELECT * FROM gcmusers WHERE email='$email'";
	$check = mysqli_fetch_array(mysqli_query($con,$sql));

	if(isset($check)){
		echo 'username or email already exist';
	}
	else{
		$sql = "INSERT INTO gcmusers(uuid, name, username, email, password) VALUES('$uuid', '$name', '$username', '$email', '$password')";
		if(mysqli_query($con,$sql)){
			echo 'Successfully Registered';
		}
		else{
		echo 'oops! Please try again!';
		}
	}
	mysqli_close($con);
	

?>
