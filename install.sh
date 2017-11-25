#!/bin/bash
if [[ $EUID -ne 0 ]]; then
	echo "You must be a root user" 2>&1
	exit 1
else
	sudo mkdir /tmp/nyt/
	cd /tmp/nyt/
	echo "Installing dependencies..."
	sudo apt install apache2 arduino python3 git
	echo "Installing ino..."
	sudo git clone git://github.com/amperka/ino.git
	cd ino/
	sudo make install
	echo "Cloning files..."
	sudo git clone https://github.com/LowderPlay/NewYearTree
	echo "Uploading code to Arduino..."
	cd /tmp/nyt/NewYearTree/arduino/WiFi_light_2/
	ino build
	ino upload
	echo "Copying files to web server..."
	sudo cp -R /tmp/nyt/NewYearTree/web/ /var/www/html/tree
	echo "Installed! You can access the web interface in http://RASPBERRY_PI_IP/tree"
fi