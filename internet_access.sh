#!/bin/bash
route add default gw 192.168.7.1 
bool_add_nameserver=$(grep -c "nameserver 8.8.8.8" /etc/resolv.conf)
if (( $bool_add_nameserver == 0 ));
then
	echo "nameserver 8.8.8.8" >> /etc/resolv.conf
fi
echo $bool_add_nameserver
timedatectl set-timezone "America/Chicago"
timedatectl set-ntp false

