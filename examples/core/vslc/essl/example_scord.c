/*******************************************************************************
* Copyright 2003-2019 Intel Corporation.
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
!    scord  Example Program Text
!******************************************************************************/

#include "sample_essl.h"

#include <stdio.h>
#include <math.h>

int main()
{
    int    inch, incx, incy;
    int    nh,   nx,   ny;
    int    iy0;
    float  h[3], x[15], y[24];
    int    i;
    double r10;
    int    r1[6] = { 2, 5, 8, 11, 14, 5 };
    int    r2[3] = { 5, 8, 11 };
/************* Initialize data *****/
    r10 = 2.0e-5;
    inch = 2;
    incx = 3;
    incy = 4;
    nh   = 2;
    nx   = 5;
    ny   = 6;
    for ( i = 0; i < nh; i++ ) h[i*inch] = (float)(i+1);
    printf("\n");
    for ( i = 0; i < nx; i++ ) x[i*incx] = (float)(i+1);

    /****** 1-st Sample **********/

    iy0 = -1;

    /***** Call scord *****/

    scord( h, inch, x, incx, y, incy, nh, nx, iy0, ny );

    /***** Printing results *****/

    printf(" 1-st Sample of scord.\n");
    printf("----------------------\n");
    printf("Parameters:\n");
    printf("    inch = %4d, incx = %4d, incy = %4d \n", inch, incx, incy );
    printf("    nh   = %4d, nx   = %4d, ny   = %4d \n", nh, nx, ny );
    printf("    iy0  = %4d \n\n", iy0 );
    for( i=0; i < nh; i++ ) printf("h[%3d ] = %4f\n",i*inch,h[i*inch]);
    printf("\n");
    for( i=0; i < nx; i++ ) printf("x[%3d ] = %4f\n",i*incx,x[i*incx]);
    printf("\n");

    printf("Results:\n");
    printf("---------------------------\n");
    for( i=0; i < ny; i++ ) printf("y[%3d ] = %4f\n",i*incy,y[i*incy]);
    for( i = 0; i < 6; i++ ) {
        if(fabs(y[i*incy]-r1[i]) > r10) {
             printf("ERROR: wrong result: i=%d, y[i*incy]=%g\n",i,y[i*incy]);
             printf("---------------------------\n");
             printf(" TEST FAILED\n");
             printf("---------------------------\n");
             return 1;
         }
    }
    printf("\n");


    /****** 2-nd Sample **********/

    iy0 = 0;
    ny  = 3;

    /***** Call scord *****/

    scord( h, inch, x, incx, y, incy, nh, nx, iy0, ny );

    /***** Printing results *****/

    printf(" 2-nd Sample of scord.\n");
    printf("----------------------\n");
    printf("Parameters:\n");
    printf("    inch = %4d, incx = %4d, incy = %4d \n", inch, incx, incy );
    printf("    nh   = %4d, nx   = %4d, ny   = %4d \n", nh, nx, ny );
    printf("    iy0  = %4d \n\n", iy0 );
    for( i=0; i < nh; i++ ) printf("h[%3d ] = %4f\n",i*inch,h[i*inch]);
    printf("\n");
    for( i=0; i < nx; i++ ) printf("x[%3d ] = %4f\n",i*incx,x[i*incx]);
    printf("\n");

    printf("Results:\n");
    printf("---------------------------\n");
    for( i=0; i < ny; i++ ) printf("y[%3d ] = %4f\n",i*incy,y[i*incy]);
    printf("\n");
    for( i = 0; i < 3; i++ ) {
        if(fabs(y[i*incy]-r2[i]) > r10) {
             printf("ERROR: wrong result: i=%d, y[i*incy]=%g\n",i,y[i*incy]);
             printf("---------------------------\n");
             printf(" TEST FAILED\n");
             printf("---------------------------\n");
             return 1;
         }
    }
    printf("---------------------------\n");
    printf(" TEST PASSED\n");
    printf("---------------------------\n");

    return 0;
}
