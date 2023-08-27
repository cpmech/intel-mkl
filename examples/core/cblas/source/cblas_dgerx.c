/*******************************************************************************
* Copyright 1999-2019 Intel Corporation.
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
!  Content:
!      C B L A S _ D G E R  Example Program Text ( C Interface )
!******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"

#include "mkl_example.h"

int main(int argc, char *argv[])
{
      FILE *in_file;
      char *in_file_name;

      MKL_INT         m, n, lda, incx, incy;
      MKL_INT         rmaxa, cmaxa;
      double          alpha;
      double         *a, *x, *y;
      CBLAS_LAYOUT    layout;
      MKL_INT         len_x, len_y;

      printf("\n     C B L A S _ D G E R   EXAMPLE PROGRAM\n");

/*       Get input parameters                                  */

      if( argc == 1 ) {
         printf("\n You must specify in_file data file as 1-st parameter");
         return 1;
      }
      in_file_name = argv[1];

/*       Get input data                                        */

      if( (in_file = fopen( in_file_name, "r" )) == NULL ) {
         printf("\n ERROR on OPEN '%s' with mode=\"r\"\n", in_file_name);
         return 1;
      }
      if( GetIntegerParameters(in_file, &m, &n) != 2 ) {
          printf("\n ERROR of m, n reading\n");
          fclose(in_file);
          return 1;
      }
      if( GetIntegerParameters(in_file, &incx, &incy) != 2 ) {
          printf("\n ERROR of incx, incy reading\n");
          fclose(in_file);
          return 1;
      }
      if( GetScalarsD(in_file, &alpha) != 1 ) {
          printf("\n ERROR of alpha reading\n");
          fclose(in_file);
          return 1;
      }
      if( GetCblasCharParameters(in_file, &layout) != 1 ) {
          printf("\n ERROR of layout reading\n");
          fclose(in_file);
          return 1;
      }

      rmaxa = m + 1;
      cmaxa = n;
      len_x = 1+(m-1)*ABS(incx);
      len_y = 1+(n-1)*ABS(incy);
      a = (double *)mkl_calloc(rmaxa*cmaxa, sizeof(double), 64);
      x = (double *)mkl_calloc(len_x, sizeof(double), 64);
      y = (double *)mkl_calloc(len_y, sizeof(double), 64);
      if( a == NULL || x == NULL || y == NULL ) {
          printf( "\n Can't allocate memory for arrays\n");
          mkl_free(a);
          mkl_free(x);
          mkl_free(y);
          fclose(in_file);
          return 1;
      }
      if( layout == CblasRowMajor )
         lda=cmaxa;
      else
         lda=rmaxa;

      if( GetVectorD(in_file, m, x, incx) != len_x ) {
        printf("\n ERROR of vector X reading\n");
        mkl_free(a);
        mkl_free(x);
        mkl_free(y);
        fclose(in_file);
        return 1;
      }
      if( GetVectorD(in_file, n, y, incy) != len_y ) {
        printf("\n ERROR of vector Y reading\n");
        mkl_free(a);
        mkl_free(x);
        mkl_free(y);
        fclose(in_file);
        return 1;
      }
      if( GetArrayD(in_file, &layout, GENERAL_MATRIX, &m,  &n,  a, &lda) != 0 ) {
        printf("\n ERROR of array A reading\n");
        mkl_free(a);
        mkl_free(x);
        mkl_free(y);
        fclose(in_file);
        return 1;
      }
      fclose(in_file);

/*       Print input data                                      */

      printf("\n     INPUT DATA");
      printf("\n       M="INT_FORMAT"  N="INT_FORMAT, m, n);
      printf("\n       ALPHA=%5.2f", alpha);
      PrintParameters("LAYOUT", layout);
      PrintVectorD(FULLPRINT, m, x, incx, "X");
      PrintVectorD(FULLPRINT, n, y, incy, "Y");
      PrintArrayD(&layout, FULLPRINT, GENERAL_MATRIX, &m, &n, a, &lda, "A");

/*      Call CBLAS_DGER subroutine ( C Interface )             */

      cblas_dger(layout, m, n, alpha, x, incx, y, incy, a, lda);

/*       Print output data                                     */

      printf("\n\n     OUTPUT DATA");
      PrintArrayD(&layout, FULLPRINT, GENERAL_MATRIX, &m, &n, a, &lda, "A");

      mkl_free(a);
      mkl_free(x);
      mkl_free(y);

      return 0;
}

