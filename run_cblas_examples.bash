#!/bin/bash

EXAMPLES="\
    dgemv \
"

cd examples/core/cblas
for ex in $EXAMPLES; do
    echo
    echo
    echo
    echo "------------------------------------------------------------------------"
    echo "COMPILING AND RUNNING <$ex>"
    make libintel64 compiler=gnu MKLROOT=/opt/intel/mkl function=cblas_$ex 1> /dev/null
    echo
    echo "RESULTS:"
    cat "_results/gnu_lp64_omp_intel64_lib/cblas_$ex.res"
done
