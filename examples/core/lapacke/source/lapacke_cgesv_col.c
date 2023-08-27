/*******************************************************************************
* Copyright 2010-2019 Intel Corporation.
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
   LAPACKE_cgesv Example.
   ======================
 
   The program computes the solution to the system of linear
   equations with a square matrix A and multiple
   right-hand sides B, where A is the coefficient matrix:
 
   (  1.23, -5.50) (  7.91, -5.38) ( -9.80, -4.86) ( -7.32,  7.57) 
   ( -2.14, -1.12) ( -9.92, -0.79) ( -9.18, -1.12) (  1.37,  0.43) 
   ( -4.30, -7.10) ( -6.47,  2.52) ( -6.51, -2.67) ( -5.86,  7.38) 
   (  1.27,  7.29) (  8.90,  6.92) ( -8.82,  1.25) (  5.41,  5.37) 

   and B is the right-hand side matrix:
 
   (  8.33, -7.32) ( -6.11, -3.81) 
   ( -6.18, -4.80) (  0.14, -7.71) 
   ( -5.71, -2.80) (  1.41,  3.40) 
   ( -1.60,  3.08) (  8.54, -4.05) 
 
   Description.
   ============
 
   The routine solves for X the system of linear equations A*X = B, 
   where A is an n-by-n matrix, the columns of matrix B are individual 
   right-hand sides, and the columns of X are the corresponding 
   solutions.

   The LU decomposition with partial pivoting and row interchanges is 
   used to factor A as A = P*L*U, where P is a permutation matrix, L 
   is unit lower triangular, and U is upper triangular. The factored 
   form of A is then used to solve the system of equations A*X = B.

   Example Program Results.
   ========================
 
 LAPACKE_cgesv (column-major, high-level) Example Program Results

 Solution
 ( -1.09, -0.18) (  1.28,  1.21)
 (  0.97,  0.52) ( -0.22, -0.97)
 ( -0.20,  0.19) (  0.53,  1.36)
 ( -0.59,  0.92) (  2.22, -1.00)

 Details of LU factorization
 ( -4.30, -7.10) ( -6.47,  2.52) ( -6.51, -2.67) ( -5.86,  7.38)
 (  0.49,  0.47) ( 12.26, -3.57) ( -7.87, -0.49) ( -0.98,  6.71)
 (  0.25, -0.15) ( -0.60, -0.37) (-11.70, -4.64) ( -1.35,  1.38)
 ( -0.83, -0.32) (  0.05,  0.58) (  0.93, -0.50) (  2.66,  7.86)

 Pivot indices
      3      3      3      4
*/
#include <stdlib.h>
#include <stdio.h>
#include "mkl_lapacke.h"

/* Auxiliary routines prototypes */
extern void print_matrix( char* desc, MKL_INT m, MKL_INT n, MKL_Complex8* a, MKL_INT lda );
extern void print_int_vector( char* desc, MKL_INT n, MKL_INT* a );

/* Parameters */
#define N 4
#define NRHS 2
#define LDA N
#define LDB N

/* Main program */
int main() {
	/* Locals */
	MKL_INT n = N, nrhs = NRHS, lda = LDA, ldb = LDB, info;
	/* Local arrays */
	MKL_INT ipiv[N];
	MKL_Complex8 a[LDA*N] = {
	   { 1.23f, -5.50f}, {-2.14f, -1.12f}, {-4.30f, -7.10f}, { 1.27f,  7.29f},
	   { 7.91f, -5.38f}, {-9.92f, -0.79f}, {-6.47f,  2.52f}, { 8.90f,  6.92f},
	   {-9.80f, -4.86f}, {-9.18f, -1.12f}, {-6.51f, -2.67f}, {-8.82f,  1.25f},
	   {-7.32f,  7.57f}, { 1.37f,  0.43f}, {-5.86f,  7.38f}, { 5.41f,  5.37f}
	};
	MKL_Complex8 b[LDB*NRHS] = {
	   { 8.33f, -7.32f}, {-6.18f, -4.80f}, {-5.71f, -2.80f}, {-1.60f,  3.08f},
	   {-6.11f, -3.81f}, { 0.14f, -7.71f}, { 1.41f,  3.40f}, { 8.54f, -4.05f}
	};
	/* Executable statements */
	printf( "LAPACKE_cgesv (column-major, high-level) Example Program Results\n" );
	/* Solve the equations A*X = B */
	info = LAPACKE_cgesv( LAPACK_COL_MAJOR, n, nrhs, a, lda, ipiv, b, ldb );
	/* Check for the exact singularity */
	if( info > 0 ) {
		printf( "The diagonal element of the triangular factor of A,\n" );
		printf( "U(%i,%i) is zero, so that A is singular;\n", info, info );
		printf( "the solution could not be computed.\n" );
		exit( 1 );
	}
	/* Print solution */
	print_matrix( "Solution", n, nrhs, b, ldb );
	/* Print details of LU factorization */
	print_matrix( "Details of LU factorization", n, n, a, lda );
	/* Print pivot indices */
	print_int_vector( "Pivot indices", n, ipiv );
	exit( 0 );
} /* End of LAPACKE_cgesv Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, MKL_INT m, MKL_INT n, MKL_Complex8* a, MKL_INT lda ) {
	MKL_INT i, j;
	printf( "\n %s\n", desc );
	for( i = 0; i < m; i++ ) {
		for( j = 0; j < n; j++ )
			printf( " (%6.2f,%6.2f)", a[i+j*lda].real, a[i+j*lda].imag );
		printf( "\n" );
	}
}

/* Auxiliary routine: printing a vector of integers */
void print_int_vector( char* desc, MKL_INT n, MKL_INT* a ) {
	MKL_INT j;
	printf( "\n %s\n", desc );
	for( j = 0; j < n; j++ ) printf( " %6i", a[j] );
	printf( "\n" );
}
