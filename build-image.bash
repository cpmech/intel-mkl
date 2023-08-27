#!/bin/bash

NAME="cpmech/intel-mkl-examples"
VERSION="latest"

echo
echo
echo "... docker .................................................."
echo "............................................................."
echo

docker build --no-cache -t $NAME:$VERSION .
docker images -q -f "dangling=true" | xargs docker rmi
