#!/bin/bash

NAME="cpmech/intel-mkl-examples"
VERSION="latest"

docker logout
docker login
docker push $NAME:$VERSION
