<?php
if(!$argv[1]) {
	echo "Search item not found!\n";
	exit(1);
}

echo $argv[1] . "\n";

// $url = "https://www.lexico.com/definition/".argv[1]; // Oxford
$url = "https://www.dictionary.com/browse/" . $argv[1];

$url_handle = fopen($url, "r"); // or die("Can not open URL handle!");
if(!$url_handle) {
	echo "Can't open URL handle!\n";
	exit(1);
}

$file_handle = fopen("/media/sayan/NAS/dictionary/".$argv[1] . ".txt", "a+");
if(!$file_handle) {
	echo "Can't Open file for writing!\n";
	exit(1);
}

if($url_handle) {
	while(!feof($url_handle)) {
		$buffer = fgets($url_handle, 4096);
		fwrite($file_handle, $buffer);
	}
	fclose($url_handle);
}

fclose($file_handle);
?>
