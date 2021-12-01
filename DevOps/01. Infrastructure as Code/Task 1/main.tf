terraform {
  required_providers {
    docker = {
      source  = "kreuzwerker/docker"
      version = "2.14.0"
    }
  }
}

provider "docker" {
  host = "tcp://192.168.99.100:2375/"
}

# One way to deliver the project's files to the Docker host
resource "null_resource" "files" {
  triggers = {
    php_image_id = docker_image.img-php.id
  }

  provisioner "remote-exec" {
    inline = [
      "sudo rm -rf /project || true",
      "sudo mkdir /project || true",
      "cd /project",
      "sudo git clone https://github.com/shekeriev/two-docker-images .",
    ]

    connection {
      type     = "ssh"
      user     = "vagrant"
      password = "vagrant"
      host     = "192.168.99.100"
    }
  }
}

resource "docker_network" "net-docker" {
  name = "dob-net"
}

resource "docker_image" "img-php" {
  name = "shekeriev/dob-w3-php"
}

resource "docker_image" "img-mysql" {
  name = "shekeriev/dob-w3-mysql"
}

resource "docker_container" "con-php" {
  name  = "dob-php"
  image = docker_image.img-php.latest
  ports {
    internal = 80
    external = 80
  }
  # Files are on the Docker host - either copied manually or by using some sort of automation
  volumes {
    host_path      = "/project/site"
    container_path = "/var/www/html"
    read_only      = true
  }
  networks_advanced {
    name = "dob-net"
  }
  depends_on = [
    null_resource.files,
  ]
}

resource "docker_container" "con-mysql" {
  name  = "dob-mysql"
  image = docker_image.img-mysql.latest
  env   = ["MYSQL_ROOT_PASSWORD=12345"]
  networks_advanced {
    name = "dob-net"
  }
}
