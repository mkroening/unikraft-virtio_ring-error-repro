#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

gcc -o client client.c
./client
