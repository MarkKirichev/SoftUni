#!/bin/bash

# Install the required packages
sudo yum install -y mariadb mariadb-server git

# Configure MariaDB to listen on all interfaces
echo 'bind-address = 0.0.0.0' | sudo tee -a /etc/my.cnf.d/server.cnf

# Enable and start the MariaDB service
sudo systemctl enable --now mariadb

# Download the project
git clone https://github.com/shekeriev/two-docker-images

# Install the database required for the web application
mysql -u root < ~/two-docker-images/mysql/sql/init.sql

# Allow the root user to connect remotely
mysql -u root -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION; FLUSH PRIVILEGES; "