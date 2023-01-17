#!/bin/bash
SPACE=$(df --output=avail -B 1 / |tail -n 1)
FREE=$(df -k / | tail -1 | awk '{print $4}')
echo "FREE_DISK_SPACE" $FREE $SPACE