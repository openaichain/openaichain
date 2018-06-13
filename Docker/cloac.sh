#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./cloac.sh
# Run single cmd:  sudo ./cloac.sh <cloac paramers>

PREFIX="docker-compose exec nodoacd cloac"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "cloac " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX "$@"
fi
