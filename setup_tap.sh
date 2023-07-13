#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

ip tuntap add tap10 mode tap
ip addr add 10.0.5.1/24 broadcast 10.0.5.255 dev tap10
ip link set dev tap10 up
echo 1 > /proc/sys/net/ipv4/conf/tap10/proxy_arp
