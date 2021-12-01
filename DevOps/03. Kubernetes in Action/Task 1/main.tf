provider "kubernetes" {
  config_path = "~/.kube/config"
}

resource "kubernetes_pod" "dob-mysql" {
  metadata {
    name = "dob-mysql"
    labels = {
      App = "mysql"
    }
  }

  spec {
    container {
      image = "shekeriev/dob-w3-mysql"
      name  = "dob-mysql"

      env {
        name  = "MYSQL_ROOT_PASSWORD"
        value = "12345"
      }

      port {
        container_port = 3306
      }
    }

    hostname = "dob-mysql"
  }
}

resource "kubernetes_pod" "dob-php" {
  metadata {
    name = "dob-php"
    labels = {
      App = "php"
    }
  }

  spec {
    container {
      image = "shekeriev/dob-w3-php"
      name  = "dob-php"

      port {
        container_port = 80
      }

      volume_mount {
        mount_path = "/var/www/html/"
        name       = "site-data"
      }
    }

    hostname = "dob-php"

    volume {
      name = "site-data"

      host_path {
        path = "/home/docker/site"
      }
    }
  }
}

resource "kubernetes_service" "dob-mysql" {
  metadata {
    name = "dob-mysql"
  }
  spec {
    selector = {
      App = "mysql"
    }
    port {
      port = 3306
    }
  }
}

resource "kubernetes_service" "dob-php" {
  metadata {
    name = "dob-php"
  }
  spec {
    selector = {
      App = "php"
    }
    port {
      port        = 80
      target_port = 80
      node_port   = 30001
    }
    type = "NodePort"
  }
}
