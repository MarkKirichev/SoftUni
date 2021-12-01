class { '::mysql::server':
  root_password           => '12345',
  remove_default_accounts => true,
  restart                 => true, 
  override_options => {
    mysqld => { bind-address => '0.0.0.0'}
  },
}

mysql::db { 'docker_info':
  user        => 'root',
  password    => '12345',
  dbname      => 'docker_info',
  host        => '%',
  sql         => '/vagrant/db/init.sql',
  enforce_sql => true, 
}

class { 'firewall': }

firewall { '000 accept 3306/tcp':
  action   => 'accept',
  dport    => 3306,
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
