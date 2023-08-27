#!/bin/bash

NAME="intelmkl"
VERSION="latest"

echo
echo
echo "... docker .................................................."
echo "............................................................."
echo

docker build --no-cache -t gosl/$NAME:$VERSION .

