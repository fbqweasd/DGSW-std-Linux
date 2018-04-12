<?php
	$server_name="localhost";
	$user_name="root";
	$password="dgsw";
	$dbname="mysql";
	$conn=new mysqli($server_name,$user_name,$password,$dbname);
	if($conn->connect_error){
		die("connection failed:".$conn->connect_error);
	}
	$sql="INSERT INTO input_web (name,address) VALUES('".$_POST[name]."','".$_POST[address]."')";

	if($conn->query($sql)===TRUE){
		echo "new record created succesfully";
	}
	else{
		echo "error".$sql . "<br>" . $conn->error;
	}
	$conn->close();



	if($_POST[led_on]){
		$a=exec("gpio -g mode 18 output");
		//echo $a;
		$b=exec("gpio -g write 18 1");
		//echo $b;
		
	}
	if($_POST[led_off]){
		$d=exec("gpio -g mode 18 output");
		//echo $d;
		$c=exec("gpio -g write 18 0");
		//echo $c;
	}
	header("Location:/input.html");
	exit;
?>
