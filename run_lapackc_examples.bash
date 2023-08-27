#!/bin/bash

EXAMPLES="\
    dgeev \
    dgesv \
    dgesvd \
    dsyev \
"

cd examples/core/lapackc
for ex in $EXAMPLES; do
    echo
    echo
    echo
    echo "------------------------------------------------------------------------"
    echo "COMPILING AND RUNNING <$ex>"
    make libintel64 compiler=gnu MKLROOT=/opt/intel/mkl function=$ex 1> /dev/null
    echo
    echo "RESULTS:"
    cat "_results/gnu_lp64_omp_intel64_lib/$ex.res"
done
