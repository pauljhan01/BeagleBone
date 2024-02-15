route add default gw 192.168.7.1 
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
timedatectl set-timezone "America/Chicago"
timedatectl set-ntp false

