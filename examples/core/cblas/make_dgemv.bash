#!/bin/bash

make libintel64 compiler=gnu MKLROOT=/opt/intel/mkl function=cblas_dgemv
