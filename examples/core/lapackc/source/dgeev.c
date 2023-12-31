/*******************************************************************************
* Copyright 2009-2019 Intel Corporation.
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
   DGEEV Example.
   ==============

   Program computes the eigenvalues and left and right eigenvectors of a general
   rectangular matrix A:

    -1.01   0.86  -4.60   3.31  -4.81
     3.98   0.53  -7.04   5.29   3.55
     3.30   8.26  -3.89   8.20  -1.51
     4.43   4.96  -7.66  -7.33   6.18
     7.31  -6.43  -6.16   2.47   5.58

   Description.
   ============

   The routine computes for an n-by-n real nonsymmetric matrix A, the
   eigenvalues and, optionally, the left and/or right eigenvectors. The right
   eigenvector v(j) of A satisfies

   A*v(j)= lambda(j)*v(j)

   where lambda(j) is its eigenvalue. The left eigenvector u(j) of A satisfies

   u(j)H*A = lambda(j)*u(j)H

   where u(j)H denotes the conjugate transpose of u(j). The computed
   eigenvectors are normalized to have Euclidean norm equal to 1 and
   largest component real.

   Example Program Results.
   ========================

 DGEEV Example Program Results

 Eigenvalues
 (  2.86, 10.76) (  2.86,-10.76) ( -0.69,  4.70) ( -0.69, -4.70) -10.46

 Left eigenvectors
 (  0.04,  0.29) (  0.04, -0.29) ( -0.13, -0.33) ( -0.13,  0.33)   0.04
 (  0.62,  0.00) (  0.62,  0.00) (  0.69,  0.00) (  0.69,  0.00)   0.56
 ( -0.04, -0.58) ( -0.04,  0.58) ( -0.39, -0.07) ( -0.39,  0.07)  -0.13
 (  0.28,  0.01) (  0.28, -0.01) ( -0.02, -0.19) ( -0.02,  0.19)  -0.80
 ( -0.04,  0.34) ( -0.04, -0.34) ( -0.40,  0.22) ( -0.40, -0.22)   0.18

 Right eigenvectors
 (  0.11,  0.17) (  0.11, -0.17) (  0.73,  0.00) (  0.73,  0.00)   0.46
 (  0.41, -0.26) (  0.41,  0.26) ( -0.03, -0.02) ( -0.03,  0.02)   0.34
 (  0.10, -0.51) (  0.10,  0.51) (  0.19, -0.29) (  0.19,  0.29)   0.31
 (  0.40, -0.09) (  0.40,  0.09) ( -0.08, -0.08) ( -0.08,  0.08)  -0.74
 (  0.54,  0.00) (  0.54,  0.00) ( -0.29, -0.49) ( -0.29,  0.49)   0.16
*/
#include <stdlib.h>
#include <stdio.h>
#include <mkl.h>

/* Auxiliary routines prototypes */
extern void print_eigenvalues( char* desc, int n, double* wr, double* wi );
extern void print_eigenvectors( char* desc, int n, double* wi, double* v,
      int ldv );

/* Parameters */
#define N 5
#define LDA N
#define LDVL N
#define LDVR N

/* Main program */
int main() {
	/* Locals */
	MKL_INT n = N, lda = LDA, ldvl = LDVL, ldvr = LDVR, info, lwork;
	double wkopt;
	double* work;
	/* Local arrays */
	double wr[N], wi[N], vl[LDVL*N], vr[LDVR*N];
	double a[LDA*N] = {
	   -1.01,  3.98,  3.30,  4.43,  7.31,
	    0.86,  0.53,  8.26,  4.96, -6.43,
	   -4.60, -7.04, -3.89, -7.66, -6.16,
	    3.31,  5.29,  8.20, -7.33,  2.47,
	   -4.81,  3.55, -1.51,  6.18,  5.58
	};
	/* Executable statements */
	printf( " DGEEV Example Program Results\n" );
	/* Query and allocate the optimal workspace */
	lwork = -1;
	dgeev( "Vectors", "Vectors", &n, a, &lda, wr, wi, vl, &ldvl, vr, &ldvr,
         &wkopt, &lwork, &info );
	lwork = (MKL_INT)wkopt;
	work = (double*)malloc( lwork*sizeof(double) );
	/* Solve eigenproblem */
	dgeev( "Vectors", "Vectors", &n, a, &lda, wr, wi, vl, &ldvl, vr, &ldvr,
         work, &lwork, &info );
	/* Check for convergence */
	if( info > 0 ) {
		printf( "The algorithm failed to compute eigenvalues.\n" );
		exit( 1 );
	}
	/* Print eigenvalues */
	print_eigenvalues( "Eigenvalues", n, wr, wi );
	/* Print left eigenvectors */
	print_eigenvectors( "Left eigenvectors", n, wi, vl, ldvl );
	/* Print right eigenvectors */
	print_eigenvectors( "Right eigenvectors", n, wi, vr, ldvr );
	/* Free workspace */
	free( (void*)work );
	exit( 0 );
} /* End of DGEEV Example */

/* Auxiliary routine: printing eigenvalues */
void print_eigenvalues( char* desc, int n, double* wr, double* wi ) {
	int j;
	printf( "\n %s\n", desc );
   for( j = 0; j < n; j++ ) {
      if( wi[j] == (double)0.0 ) {
         printf( " %6.2f", wr[j] );
      } else {
         printf( " (%6.2f,%6.2f)", wr[j], wi[j] );
      }
   }
   printf( "\n" );
}

/* Auxiliary routine: printing eigenvectors */
void print_eigenvectors( char* desc, int n, double* wi, double* v, int ldv ) {
	int i, j;
	printf( "\n %s\n", desc );
   for( i = 0; i < n; i++ ) {
      j = 0;
      while( j < n ) {
         if( wi[j] == (double)0.0 ) {
            printf( " %6.2f", v[i+j*ldv] );
            j++;
         } else {
            printf( " (%6.2f,%6.2f)", v[i+j*ldv], v[i+(j+1)*ldv] );
            printf( " (%6.2f,%6.2f)", v[i+j*ldv], -v[i+(j+1)*ldv] );
            j += 2;
         }
      }
      printf( "\n" );
   }
}
