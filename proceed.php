<?php
$device = "/dev/ttyACM0"; //Arduino serial port (can be known with "ls /dev/")
$url = "192.168.1.127"; //Raspberry pi IP address


exec('stty -F '.$device.' ispeed 9600 ospeed 9600 -ignpar cs8 -cstopb -echo -hupcl');
$color = $_GET['color'];
if ($_GET['rainbow'] == "true") {
        $color = "220011";
} 
list($r, $g, $b) = sscanf(strval($color), "%02x%02x%02x");
print_r(array($r, $g, $b));
$send = "";
foreach(array($r, $g, $b) as $number) {
        $string = sprintf( "%03d", $number);
        $send .= $string;
}
exec("echo '".$send."' > ".$device);
header('Location: http://'.$url.'/tree/');
?>