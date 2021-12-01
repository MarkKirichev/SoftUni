if $facts['os']['family'] == 'RedHat' {
  $vpackage = 'httpd'
}
else {
  $vpackage = 'apache2'
}

package { $vpackage: }

service { $vpackage:
  ensure => running,
  enable => true,
}

file {'/var/www/html/index.html':
  ensure  => 'file',
  source => "/vagrant/web/index.html",
}

file {'/var/www/html/puppet-logo.png':
  ensure  => 'file',
  source => "/vagrant/web/puppet-logo.png",
}
