job "homework" {
  datacenters = ["dc1"]

  type = "service"

  group "homework" {
    count = 1

    network {
      port "http" {
        static = 80
      }

      port "db" {
        static = 3306
      }
    }

    task "dob-mysql" {
      driver = "docker"

      config {
        image = "shekeriev/dob-w3-mysql"

        ports = ["db"]
      }

      env {
        MYSQL_ROOT_PASSWORD = "12345"
      }

      resources {
        cpu    = 500 # 500 MHz
        memory = 256 # 256MB
      }

      service {
        name = "dob-mysql"
        tags = ["global", "db"]
        port = "db"

        check {
          name     = "alive"
          type     = "tcp"
          interval = "10s"
          timeout  = "2s"
        }
      }
    }

    task "dob-php" {
      driver = "docker"      

      config {
        image = "shekeriev/dob-w3-php"

        ports = ["http"]

        mounts = [
          {
            type = "bind"
            target = "/var/www/html"
            source = "/vagrant/site"
            readonly = true
          }
        ]
      }

      resources {
        cpu    = 500 # 500 MHz
        memory = 256 # 256MB
      }

      service {
        name = "dob-php"
        tags = ["global", "web"]
        port = "http"

        check {
          name     = "alive"
          type     = "tcp"
          interval = "10s"
          timeout  = "2s"
        }
      }
    }
  }
}
