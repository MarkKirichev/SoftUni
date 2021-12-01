bind_addr = "%SERVER_ADDRESS%" # the default

addresses {
    http = "%SERVER_ADDRESS%"
    rpc = "%SERVER_ADDRESS%"
    serf = "%SERVER_ADDRESS%"
}

# Advertise an accessible IP address so the server is reachable by other servers
# and clients. The IPs can be materialized by Terraform or be replaced by an
# init script.
advertise {
    http = "%SERVER_ADDRESS%:4646"
    rpc = "%SERVER_ADDRESS%:4647"
    serf = "%SERVER_ADDRESS%:4648"
}

# Increase log verbosity
log_level = "DEBUG"

# Setup data dir
data_dir = "/opt/nomad"

# Enable the server
server {
  enabled = true

  # Self-elect, should be 3 or 5 for production
  bootstrap_expect = 3
}

# Enable the client
client {
  enabled = true

  network_interface = "%CLIENT_INTERFACE%"
}

# Enable Docker volumes
plugin "docker" {
  config {
    volumes {
      enabled = true
    }
  }
}