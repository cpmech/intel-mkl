#!/bin/bash

set -e

EXAMPLES="\
    dgeev \
    dgesv \
    dgesvd \
    dsyev \
    zgesv \
    zgesvd \
"

cd examples/core/lapacke
for ex in $EXAMPLES; do
    echo
    echo
    echo
    echo "------------------------------------------------------------------------"
    echo "COMPILING AND RUNNING <$ex>"
    make libintel64 compiler=gnu MKLROOT=/opt/intel/mkl function=lapacke_${ex}_col 1> /dev/null
    echo
    echo "RESULTS:"
    cat "_results/gnu_lp64_omp_intel64_lib/lapacke_${ex}_col.res"
done
