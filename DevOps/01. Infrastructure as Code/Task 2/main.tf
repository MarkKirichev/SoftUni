provider "aws" {
  access_key = "<YOUR-ACCESS-KEY>"
  secret_key = "<YOUR-SECRET-KEY>"
  region     = "eu-central-1"
}

resource "aws_vpc" "dof-hw-vpc" {
  cidr_block           = "10.10.0.0/16"
  enable_dns_hostnames = true
  enable_dns_support   = true
  tags = {
    Name = "DOF-HW-VPC"
  }
}

resource "aws_internet_gateway" "dof-hw-igw" {
  vpc_id = aws_vpc.dof-hw-vpc.id
  tags = {
    Name = "DOF-HW-IGW"
  }
}

resource "aws_route_table" "dof-hw-prt" {
  vpc_id = aws_vpc.dof-hw-vpc.id
  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.dof-hw-igw.id
  }
  tags = {
    Name = "DOF-HW-PUBLIC-PRT"
  }
}

resource "aws_subnet" "dof-hw-snet" {
  vpc_id                  = aws_vpc.dof-hw-vpc.id
  cidr_block              = "10.10.10.0/24"
  map_public_ip_on_launch = true
  tags = {
    Name = "DOF-HW-SUB-NET"
  }
}

resource "aws_route_table_association" "dof-hw-prt-assoc" {
  subnet_id      = aws_subnet.dof-hw-snet.id
  route_table_id = aws_route_table.dof-hw-prt.id
}

resource "aws_security_group" "dof-hw-pub-sg" {
  name        = "dof-hw-pub-sg"
  description = "DOF HW Public SG"
  vpc_id      = aws_vpc.dof-hw-vpc.id
  ingress {
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  ingress {
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  ingress {
    from_port   = 3306
    to_port     = 3306
    protocol    = "tcp"
    cidr_blocks = ["10.10.10.0/24"]
  }
  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_network_interface" "dof-hw-web-net" {
  subnet_id       = aws_subnet.dof-hw-snet.id
  private_ips     = ["10.10.10.100"]
  security_groups = [aws_security_group.dof-hw-pub-sg.id]

  tags = {
    Name = "DOF-HW-WEB-PRIVATE-IP"
  }
}

resource "aws_network_interface" "dof-hw-db-net" {
  subnet_id       = aws_subnet.dof-hw-snet.id
  private_ips     = ["10.10.10.101"]
  security_groups = [aws_security_group.dof-hw-pub-sg.id]

  tags = {
    Name = "DOF-HW-DB-PRIVATE-IP"
  }
}

resource "aws_instance" "dof-hw-web" {
  ami           = "ami-dd3c0f36"
  instance_type = "t2.micro"
  key_name      = "dof-hw-key"

  network_interface {
    network_interface_id = aws_network_interface.dof-hw-web-net.id
    device_index         = 0
  }

  provisioner "file" {
    source      = "./provision-web.sh"
    destination = "/tmp/provision-web.sh"
    connection {
      type        = "ssh"
      user        = "centos"
      private_key = file("C:\\dof-hw-key.pem")
      host        = self.public_ip
    }
  }
  provisioner "remote-exec" {
    inline = [
      "chmod +x /tmp/provision-web.sh",
      "/tmp/provision-web.sh"
    ]
    connection {
      type        = "ssh"
      user        = "centos"
      private_key = file("C:\\dof-hw-key.pem")
      host        = self.public_ip
    }
  }
}

resource "aws_instance" "dof-hw-db" {
  ami           = "ami-dd3c0f36"
  instance_type = "t2.micro"
  key_name      = "dof-hw-key"

  network_interface {
    network_interface_id = aws_network_interface.dof-hw-db-net.id
    device_index         = 0
  }

  provisioner "file" {
    source      = "./provision-db.sh"
    destination = "/tmp/provision-db.sh"
    connection {
      type        = "ssh"
      user        = "centos"
      private_key = file("C:\\dof-hw-key.pem")
      host        = self.public_ip
    }
  }
  provisioner "remote-exec" {
    inline = [
      "chmod +x /tmp/provision-db.sh",
      "/tmp/provision-db.sh"
    ]
    connection {
      type        = "ssh"
      user        = "centos"
      private_key = file("C:\\dof-hw-key.pem")
      host        = self.public_ip
    }
  }
}

output "web_app_public_ip" {
  value = aws_instance.dof-hw-web.public_ip
}
