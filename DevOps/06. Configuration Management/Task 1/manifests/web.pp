# Set a global package parameter
Package { ensure => 'installed' }

# List the required packages
$enhancers = [ 'httpd', 'php', 'php-mysqlnd' ]

# Install the required packages
package { $enhancers: }

service { httpd:
  ensure => running,
  enable => true,
}

file { '/var/www/html/index.php':
  ensure => present,
  source => "/vagrant/web/index.php",
}

file { '/var/www/html/docker.png':
  ensure => present,
  source => "/vagrant/web/docker.png",
}

class { 'firewall': }

firewall { '000 accept 80/tcp':
  action   => 'accept',
  dport    => 80,
  proto    => 'tcp',
}

host { 'web':
  ip           => '192.168.50.2',
  host_aliases => 'dob-php',
}

host { 'db':
  ip           => '192.168.50.3',
  host_aliases => 'dob-mysql',
}

# Allow Apache to connect over network
selboolean { 'Apache SELinux':
  name       => 'httpd_can_network_connect', 
  persistent => true, 
  provider   => getsetsebool, 
  value      => on, 
}
