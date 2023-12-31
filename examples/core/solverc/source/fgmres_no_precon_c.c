/*******************************************************************************
* Copyright 2005-2019 Intel Corporation.
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
*  Content:
*  Intel(R) MKL RCI (P)FGMRES ((Preconditioned) Flexible Generalized Minimal
*                                                       RESidual method) example
********************************************************************************/

/*---------------------------------------------------------------------------
*  Example program for solving non-symmetric indefinite system of equations
*  Simplest case: no preconditioning and no user-defined stopping tests
*---------------------------------------------------------------------------*/

#include <stdio.h>
#include "mkl_rci.h"
#include "mkl_blas.h"
#include "mkl_spblas.h"
#include "mkl_service.h"
#define N 5
#define size 128

int main (void)
{

  /*---------------------------------------------------------------------------
  * Define arrays for the upper triangle of the coefficient matrix
  * Compressed sparse row storage is used for sparse representation
  *---------------------------------------------------------------------------*/
  MKL_INT ia[6] = { 1, 3, 6, 9, 12, 14 };
  MKL_INT ja[13] = 
  { 1,    3,
    1, 2,    4,
       2, 3,    5,
          3, 4, 5,
             4, 5
  };
  double A[13] = 
  { 1.0,      -1.0,
   -1.0, 1.0,      -1.0,
         1.0, -2.0,       1.0,
              -1.0, 2.0, -1.0,
                   -1.0, -3.0
  };
  /*---------------------------------------------------------------------------
  * Allocate storage for the ?par parameters and the solution/rhs vectors
  *---------------------------------------------------------------------------*/
  MKL_INT ipar[size];
  double dpar[size], tmp[N * (2 * N + 1) + (N * (N + 9)) / 2 + 1] = {0.0};
  double expected_solution[N] = { -1.0, 1.0, 0.0, 1.0, -1.0 };
  double rhs[N] = {0.0};
  double computed_solution[N] = {0.0};
  /*---------------------------------------------------------------------------
  * Some additional variables to use with the RCI (P)FGMRES solver
  *---------------------------------------------------------------------------*/
  MKL_INT itercount, expected_itercount = 5;
  MKL_INT RCI_request, i, ivar;
  double dvar;

  // Descriptor of main sparse matrix properties
  struct matrix_descr descrA, descrL;
  // Structure with sparse matrix stored in CSR format
  sparse_matrix_t       csrA, csrL;
  sparse_operation_t    transA = SPARSE_OPERATION_NON_TRANSPOSE;
  descrA.type = SPARSE_MATRIX_TYPE_GENERAL;
  descrA.mode = SPARSE_FILL_MODE_UPPER;
  descrA.diag = SPARSE_DIAG_NON_UNIT;
  mkl_sparse_d_create_csr ( &csrA, SPARSE_INDEX_BASE_ONE, N, N, ia, ia+1, ja, A );
  printf ("--------------------------------------------------\n");
  printf ("The SIMPLEST example of usage of RCI FGMRES solver\n");
  printf ("to solve a non-symmetric indefinite non-degenerate\n");
  printf ("       algebraic system of linear equations\n");
  printf ("--------------------------------------------------\n\n");
  /*---------------------------------------------------------------------------
  * Initialize variables and the right hand side through matrix-vector product
  *---------------------------------------------------------------------------*/
  ivar = N;
  mkl_sparse_d_mv( transA, 1.0, csrA, descrA, expected_solution, 0.0, rhs);
  /*---------------------------------------------------------------------------
  * Initialize the initial guess
  *---------------------------------------------------------------------------*/
  for (i = 0; i < N; i++)
    {
      computed_solution[i] = 1.0;
    }
  /*---------------------------------------------------------------------------
  * Initialize the solver
  *---------------------------------------------------------------------------*/
  dfgmres_init (&ivar, computed_solution, rhs, &RCI_request, ipar, dpar, tmp);
  if (RCI_request != 0)
    goto FAILED;
  /*---------------------------------------------------------------------------
  * Set the desired parameters:
  * LOGICAL parameters:
  * do residual stopping test
  * do not request for the user defined stopping test
  * do the check of the norm of the next generated vector automatically
  * DOUBLE PRECISION parameters
  * set the relative tolerance to 1.0D-3 instead of default value 1.0D-6
  *---------------------------------------------------------------------------*/
  ipar[8] = 1;
  ipar[9] = 0;
  ipar[11] = 1;
  dpar[0] = 1.0E-3;
  /*---------------------------------------------------------------------------
  * Check the correctness and consistency of the newly set parameters
  *---------------------------------------------------------------------------*/
  dfgmres_check (&ivar, computed_solution, rhs, &RCI_request, ipar, dpar, tmp);
  if (RCI_request != 0)
    goto FAILED;
  /*---------------------------------------------------------------------------
  * Print the info about the RCI FGMRES method
  *---------------------------------------------------------------------------*/
  printf ("Some info about the current run of RCI FGMRES method:\n\n");
  if (ipar[7])
    {
      printf ("As ipar[7]=%d, the automatic test for the maximal number of ", ipar[7]);
      printf ("iterations will be\nperformed\n");
    }
  else
    {
      printf ("As ipar[7]=%d, the automatic test for the maximal number of ", ipar[7]);
      printf ("iterations will be\nskipped\n");
    }
  printf ("+++\n");
  if (ipar[8])
    {
      printf ("As ipar[8]=%d, the automatic residual test will be performed\n", ipar[8]);
    }
  else
    {
      printf ("As ipar[8]=%d, the automatic residual test will be skipped\n", ipar[8]);
    }
  printf ("+++\n");
  if (ipar[9])
    {
      printf ("As ipar[9]=%d, the user-defined stopping test will be ", ipar[9]);
      printf ("requested via\nRCI_request=2\n");
    }
  else
    {
      printf ("As ipar[9]=%d, the user-defined stopping test will not be ", ipar[9]);
      printf ("requested, thus,\nRCI_request will not take the value 2\n");
    }
  printf ("+++\n");
  if (ipar[10])
    {
      printf ("As ipar[10]=%d, the Preconditioned FGMRES iterations will be ", ipar[10]);
      printf ("performed, thus,\nthe preconditioner action will be requested via");
      printf ("RCI_request=3\n");
    }
  else
    {
      printf ("As ipar[10]=%d, the Preconditioned FGMRES iterations will not ", ipar[10]);
      printf ("be performed,\nthus, RCI_request will not take the value 3\n");
    }
  printf ("+++\n");
  if (ipar[11])
    {
      printf ("As ipar[11]=%d, the automatic test for the norm of the next ", ipar[11]);
      printf ("generated vector is\nnot equal to zero up to rounding and ");
      printf ("computational errors will be performed,\nthus, RCI_request will not take the value 4\n");
    }
  else
    {
      printf ("As ipar[11]=%d, the automatic test for the norm of the next ", ipar[11]);
      printf ("generated vector is\nnot equal to zero up to rounding and ");
      printf ("computational errors will be skipped,\nthus, the user-defined test ");
      printf ("will be requested via RCI_request=4\n");
    }
  printf ("+++\n\n");
  /*---------------------------------------------------------------------------
  * Compute the solution by RCI (P)FGMRES solver without preconditioning
  * Reverse Communication starts here
  *---------------------------------------------------------------------------*/
ONE:dfgmres (&ivar, computed_solution, rhs, &RCI_request, ipar, dpar, tmp);
  /*---------------------------------------------------------------------------
  * If RCI_request=0, then the solution was found with the required precision
  *---------------------------------------------------------------------------*/
  if (RCI_request == 0)
    goto COMPLETE;
  /*---------------------------------------------------------------------------
  * If RCI_request=1, then compute the vector A*tmp[ipar[21]-1]
  * and put the result in vector tmp[ipar[22]-1]
  *---------------------------------------------------------------------------
  * NOTE that ipar[21] and ipar[22] contain FORTRAN style addresses,
  * therefore, in C code it is required to subtract 1 from them to get C style
  * addresses
  *---------------------------------------------------------------------------*/
  if (RCI_request == 1)
    {
      mkl_sparse_d_mv( transA, 1.0, csrA, descrA, &tmp[ipar[21] - 1], 0.0, &tmp[ipar[22] - 1]);
      goto ONE;
    }
  /*---------------------------------------------------------------------------
  * If RCI_request=anything else, then dfgmres subroutine failed
  * to compute the solution vector: computed_solution[N]
  *---------------------------------------------------------------------------*/
  else
    {
      goto FAILED;
    }
  /*---------------------------------------------------------------------------
  * Reverse Communication ends here
  * Get the current iteration number and the FGMRES solution (DO NOT FORGET to
  * call dfgmres_get routine as computed_solution is still containing
  * the initial guess!)
  *---------------------------------------------------------------------------*/
COMPLETE:dfgmres_get (&ivar, computed_solution, rhs, &RCI_request, ipar, dpar, tmp, &itercount);
     /*---------------------------------------------------------------------------
     * Print solution vector: computed_solution[N] and the number of iterations: itercount
     *--------------------------------------------------------------------------- */
  printf (" The system has been solved \n");
  printf ("\n The following solution has been obtained: \n");
  for (i = 0; i < N; i++)
    {
      printf ("computed_solution[%d]=", i);
      printf ("%e\n", computed_solution[i]);
    }
  printf ("\n The expected solution is: \n");
  for (i = 0; i < N; i++)
    {
      printf ("expected_solution[%d]=", i);
      printf ("%e\n", expected_solution[i]);
      expected_solution[i] -= computed_solution[i];
    }
  printf ("\n Number of iterations: %d\n", itercount);
  i = 1;
  dvar = dnrm2 (&ivar, expected_solution, &i);

  /*-------------------------------------------------------------------------*/
  /* Release internal Intel(R) MKL memory that might be used for computations         */
  /* NOTE: It is important to call the routine below to avoid memory leaks   */
  /* unless you disable Intel(R) MKL Memory Manager                                   */
  /*-------------------------------------------------------------------------*/
  MKL_Free_Buffers ();

  if (itercount == expected_itercount && dvar < 1.0e-14)
    {
      printf ("\nThis example has successfully PASSED through all steps of computation!\n");
      return 0;
    }
  else
    {
      printf ("\nThis example may have FAILED as either the number of iterations differs\n");
      printf ("from the expected number of iterations %d, ", expected_itercount);
      printf ("or the computed solution\n");
      printf ("differs much from the expected solution (Euclidean norm is %e), or both.\n", dvar);
      return 1;
    }
  /*-------------------------------------------------------------------------*/
  /* Release internal Intel(R) MKL memory that might be used for computations         */
  /* NOTE: It is important to call the routine below to avoid memory leaks   */
  /* unless you disable Intel(R) MKL Memory Manager                                   */
  /*-------------------------------------------------------------------------*/
FAILED:printf ("\nThis example FAILED as the solver has returned the ERROR code %d", RCI_request);
  mkl_sparse_destroy(csrA);
  MKL_Free_Buffers ();
  return 1;
}
