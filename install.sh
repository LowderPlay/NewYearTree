#!/bin/bash
if [[ $EUID -ne 0 ]]; then
	echo "You must be a root user" 2>&1
	exit 1
else
	echo "Installing dependencies..."
	sudo apt install apache2 stty arduino python3 git
	echo "Installing ino..."
	sudo pip3 install ino
	echo "Cloning files..."
	sudo mkdir /tmp/nyt/
	cd /tmp/nyt/
	sudo git clone https://github.com/LowderPlay/NewYearTree
	echo "Uploading code to Arduino..."
	cd /tmp/nyt/arduino/WiFi_light_2/
	ino build
	ino upload
	echo "Copying files to web server..."
	sudo cp -R /tmp/nyt/web/ /var/www/html/
	echo "Installed! You can access the web interface in http://RASPBERRY_PI_IP/tree"
fi