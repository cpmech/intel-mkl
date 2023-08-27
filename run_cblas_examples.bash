#!/bin/bash

set -e

EXAMPLES="\
    dasum \
    daxpy \
    dcopy \
    ddot \
    dnrm2 \
    dgemm \
    dgemv \
    dger \
    dscal \
    dsymm \
    dsymv \
    dsyrk \
    idamax \
    zaxpy \
    zcopy \
    zgemm \
    zgemv \
    zherk \
    zscal \
    zsyrk \
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
    cat "_results/gnu_lp64_parallel_intel64_lib/cblas_${ex}x.res"
    echo
done
