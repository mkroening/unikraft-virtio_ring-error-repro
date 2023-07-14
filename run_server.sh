#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

UK_DEFCONFIG="$PWD/${0%/*}/config" make defconfig

make

sudo qemu-system-x86_64 \
    -m 1G \
    -nographic \
    -nic tap,ifname=tap10,script=no,downscript=no,model=virtio-net-pci \
    -kernel build/virtio_ring-repro_qemu-x86_64 \
    -append "netdev.ipv4_addr=10.0.5.3 netdev.ipv4_subnet_mask=255.255.255.0 netdev.ipv4_gw_addr=10.0.5.1 --"
