/*******************************************************************************
* Copyright 2006-2019 Intel Corporation.
*
* This software and the related documents are Intel copyrighted  materials,  and
* your use of  them is  governed by the  express license  under which  they were
* provided to you (License).  Unless the License provides otherwise, you may not
* use, modify, copy, publish, distribute,  disclose or transmit this software or
* the related documents without Intel's prior written permission.
*
* This software and the related documents  are provided as  is,  with no express
* or implied  warranties,  other  than those  that are  expressly stated  in the
* License.
*******************************************************************************/

/*
! Content:
!          Intel(R) MKL DFTI implementation through FFTW interface (via wrappers) example
!          program (C-interface)
!
! Real 1D transform for double/single precision data not inplace.
!
! Configuration parameters for Intel(R) MKL DFTI:
!           DFTI_FORWARD_DOMAIN = DFTI_REAL        (obligatory)
!           DFTI_PRECISION      = DFTI_DOUBLE/DFTI_SINGLE (obligatory)
!           DFTI_DIMENSION      = 1                (obligatory)
!           DFTI_LENGTHS        = n                (obligatory)
!           DFTI_PLACEMENT      = DFTI_NOT_INPLACE (default=DFTI_INPLACE)
!           DFTI_FORWARD_SCALE  = 1.0              (default)
!           DFTI_BACKWARD_SCALE = 1.0/n            (default=1.0)
!
! Other default configuration parameters are in the mkl_dfti.h interface file
!****************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rfftw.h"
#include "mkl_dfti_examples.h"

int main(void)  /* REAL_1D_EX4 */
{
    /*
    **  DFT input parameters
    */
    int n = 4;
    int rank = 1;
    int multiple = 2;
    int istride = 2;
    int idist = 20;
    int ostride = 3;
    int odist = 20;
    int nn, lda, lda_out;

    rfftwnd_plan my_plan;
    fftw_real* x_in;
    fftw_complex* x_out;
    fftw_real* x_exp;

    TYPE_PRECISION Scale;
    TYPE_PRECISION maxerr;
    TYPE_PRECISION eps = EPS;

    if (LEGEND_PRINT) {
        printf("\n\n REAL_1D_EX4\n");
        printf(" Forward-Backward 1D complex transform for double/single precision data\n\n");
        printf(" Configuration parameters:\n\n");
        printf(" DFTI_FORWARD_DOMAIN = DFTI_REAL\n");
        printf(" DFTI_PRECISION      = DFTI_DOUBLE/DFTI_SINGLE\n");
        printf(" DFTI_DIMENSION      = 1\n");
        printf(" DFTI_LENGTHS        = %d\n", n);
        printf(" DFTI_PLACEMENT      = DFTI_NOT_INPLACE\n");
        printf(" DFTI_FORWARD_SCALE  = 1.0\n");
        printf(" DFTI_BACKWARD_SCALE = 1.0/n\n\n");
    }

    /*
    **  Allocate array for input/output and expected data
    */
    nn = n/2+1;
    lda = n*istride*multiple;
    if (idist > n*istride) lda = idist*multiple;
    lda_out = nn*ostride*multiple;
    if (odist > nn*ostride) lda_out = odist*multiple;

    x_in = (fftw_real*)fftw_malloc(lda*sizeof(TYPE_PRECISION));
    x_exp = (fftw_real*)fftw_malloc(lda*sizeof(TYPE_PRECISION));
    x_out = (fftw_complex*)fftw_malloc(2*lda_out*sizeof(TYPE_PRECISION));

    /*
    **  Initialize x_in and copy to expected x_exp
    */
#ifdef MKL_DOUBLE
    zero_init_d(x_in, lda);
    init_real_vectors_d(x_in, lda);
    cblas_dcopy(lda, x_in, 1, x_exp, 1);
#else
    zero_init_s(x_in, lda);
    init_real_vectors_s(x_in, lda);
    cblas_scopy(lda, x_in, 1, x_exp, 1);
#endif

    /*
    **  Create FFTW plan for 1D double/single precision forward transform
    */
    my_plan = rfftwnd_create_plan(rank, &n, FFTW_REAL_TO_COMPLEX, FFTW_ESTIMATE);
    DIE_UNLESS(my_plan);

    /*
    **  Compute DFT
    */
    rfftwnd_real_to_complex(my_plan, multiple, x_in, istride, idist, x_out, ostride, odist);

    /*
    **  Destroy FFTW plan
    */
    rfftwnd_destroy_plan(my_plan);

    /*
    **  Set Scale number for Backward transform
    */
    Scale = 1.0/(TYPE_PRECISION)n;

    /*
    **  Create FFTW plan for 1D double/single precision backward transform
    */
    my_plan = rfftwnd_create_plan(rank, &n, FFTW_COMPLEX_TO_REAL, FFTW_ESTIMATE);
    DIE_UNLESS(my_plan);

    /*
    **  Compute DFT
    */
    rfftwnd_complex_to_real(my_plan, multiple, x_out, ostride, odist, x_in, istride, idist);

    /*
    **  Destroy FFTW plan
    */
    rfftwnd_destroy_plan(my_plan);

    /*
    **  Result scaling
    */
    scaling_r_multiple(x_in, Scale, n, multiple, istride, idist);

    /*
    **  Check result
    */
    maxerr = check_result_multiple(x_in, x_exp, n, multiple, istride, idist);

    /*
    **  Free arrays for input/outout and expected data
    */
    fftw_free(x_in);
    fftw_free(x_out);
    fftw_free(x_exp);

    if (ACCURACY_PRINT)
        printf("\n Accuracy = %g\n\n", maxerr);

    if (maxerr < eps) {
        printf(" TEST PASSED\n");
    } else {
        printf(" TEST FAILED\n");
        return 1;
    }

    printf(" END OF TEST\n");

    return 0;
}
