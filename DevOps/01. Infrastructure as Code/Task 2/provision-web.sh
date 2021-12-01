#!/bin/bash

# Install the required packages
sudo yum install -y httpd php php-mysql git 

# Switch the SELinux to permissive mode
sudo setenforce 0

# Enable and start the Apache2 service
sudo systemctl enable --now httpd

# Download the project
git clone https://github.com/shekeriev/two-docker-images

# Copy the files related to the web application
sudo cp ~/two-docker-images/site/* /var/www/html

# Substitute MariaDB related connection parameters
sudo sed -i 's/dob-mysql/10.10.10.101/g' /var/www/html/index.php
sudo sed -i 's/12345//g' /var/www/html/index.php