#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

KRAFTKIT_LOG_LEVEL=debug KRAFTKIT_LOG_TYPE=basic kraft build

sudo qemu-system-x86_64 \
    -m 1G \
    -nographic \
    -nic tap,ifname=tap10,script=no,downscript=no,model=virtio-net-pci \
    -kernel .unikraft/build/default_qemu-x86_64 \
    -append "netdev.ipv4_addr=10.0.5.3 netdev.ipv4_subnet_mask=255.255.255.0 netdev.ipv4_gw_addr=10.0.5.1 --"
