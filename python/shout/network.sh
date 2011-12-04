#!/bin/sh

#ifconfig eth0 down
#ifconfig eth0 up

ifconfig eth0 192.168.0.124 netmask 255.255.255.0
route del default
route add default gw 192.168.0.1

echo 'nameserver 59.187.192.80' > /etc/resolv.conf
