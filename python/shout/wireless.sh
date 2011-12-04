#!/bin/sh

ifconfig wlan0 down
ifconfig wlan0 up

iwconfig wlan0 essid "iptime"
iwconfig wlan0 mode managed
iwconfig wlan0 channel auto
iwconfig wlan0 key off

ifconfig wlan0 192.168.0.254 netmask 255.255.255.0
route del default
route add default gw 192.168.0.1

echo 'nameserver 59.187.192.80' > /etc/resolv.conf
