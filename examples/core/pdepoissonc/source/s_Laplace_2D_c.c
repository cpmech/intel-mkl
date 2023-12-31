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
*  Content:
*  C real example of solving 2D Laplace problem in a
*  rectangular domain using Intel(R) MKL Poisson Library
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mkl_service.h"
/* Include Poisson Library header files */
#include "mkl_poisson.h"

int main(void)
{
  MKL_INT nx=6, ny=6;

  MKL_INT ix, iy, i, stat;
  MKL_INT ipar[128];
  float ax, bx, ay, by, lx, ly, hx, hy, xi, yi, c1;
  float *spar=NULL, *f=NULL, *u=NULL, *bd_ax=NULL, *bd_bx=NULL, *bd_ay=NULL, *bd_by=NULL;
  float q;
  DFTI_DESCRIPTOR_HANDLE xhandle = 0;
  char *BCtype;
  MKL_INT mem_error, error;

  /* Printing the header for the example */
  printf("\n Example of use of Intel(R) MKL Poisson Library\n");
  printf(" **********************************************\n\n");
  printf(" This example gives the solution of the 2D Laplace problem\n");
  printf(" with the equation u_xx+u_yy=0, 0<x<1, 0<y<1,\n");
  printf(" with the following boundary conditions:\n");
  printf(" u(0,y)=  y^4\n");
  printf(" u(1,y)=1+y^4-6*(y^2)\n");
  printf(" u(x,0)=x^4\n");
  printf(" u(x,1)=x^4+1-6*(x^2)\n");
  printf(" ----------------------------------------------------------------------\n");
  printf(" In general, the error should be of order O(1.0/nx^2+1.0/ny^2)\n");
  printf(" For this example, the value of nx=ny is %d\n", nx);
  printf(" The approximation error should be of order 5.0e-03,");
  printf(" if everything is OK\n");
  printf(" ----------------------------------------------------------------------\n");
  printf("                      SINGLE PRECISION COMPUTATIONS                    \n");
  printf(" ======================================================================\n");
  printf("\n");

  error = 0;
  /* memory allocation */
  mem_error = 1;
  spar=(float*)mkl_malloc((13*nx/2+7)*sizeof(float), 64);
  if(spar == NULL) goto end;
  f=(float*)mkl_malloc((nx+1)*(ny+1)*sizeof(float), 64);
  if(f == NULL) goto end;
  u=(float*)mkl_malloc((nx+1)*(ny+1)*sizeof(float), 64);
  if(u == NULL) goto end;
  bd_ax=(float*)mkl_malloc((ny+1)*sizeof(float), 64);
  if(bd_ax == NULL) goto end;
  bd_bx=(float*)mkl_malloc((ny+1)*sizeof(float), 64);
  if(bd_bx == NULL) goto end;
  bd_ay=(float*)mkl_malloc((nx+1)*sizeof(float), 64);
  if(bd_ay == NULL) goto end;
  bd_by=(float*)mkl_malloc((nx+1)*sizeof(float), 64);
  if(bd_by == NULL) goto end;
  /* memory allocated correctly */
  mem_error = 0;

  /* Defining the rectangular domain 0<x<1, 0<y<1 for 2D Laplace Solver */
  ax=0.0E0;
  bx=1.0E0;
  ay=0.0E0;
  by=1.0E0;

  /*******************************************************************************
  Setting the coefficient q to 0.
  Note that this is the first of two steps on the way to use Helmholtz Solver
  to solve Laplace problem!
  *******************************************************************************/
  q=0.0E0;

  /* Computing the mesh size hx in x-direction */
  lx=bx-ax;
  hx=lx/nx;
  /* Computing the mesh size hy in y-direction */
  ly=by-ay;
  hy=ly/ny;

  /* Filling in the values of the TRUE solution u(x,y)=x^4+y^4-6*(y^2)*(x^2)
  in the mesh points into the array u
  *******************************************************************************
  Filling in the right-hand side f(x,y)=0.0 in the mesh points into the array f.
  Note that this the second of two steps on the way to use Helmholtz Solver
  to solve Laplace problem. Current implementation of Poisson Library requires
  the array f for the solution of Laplace problem
  *******************************************************************************
  Here we are using the mesh sizes hx and hy computed before to compute
  the coordinates (xi,yi) of the mesh points */
  for(iy=0;iy<=ny;iy++)
  {
    for(ix=0;ix<=nx;ix++)
    {
      xi=hx*ix/lx;
      yi=hy*iy/ly;

      u[ix+iy*(nx+1)]=xi*xi*xi*xi+yi*yi*yi*yi-6.0E0*(yi*yi)*(xi*xi);
      f[ix+iy*(nx+1)]=0.0E0;
    }
  }

  /* Setting the type of the boundary conditions on each side
  of the rectangular domain:
  On the boundary laying on the line x=0(=ax) Dirichlet boundary condition
  will be used
  On the boundary laying on the line x=1(=bx) Dirichlet boundary condition
  will be used
  On the boundary laying on the line y=0(=ay) Dirichlet boundary condition
  will be used
  On the boundary laying on the line y=1(=by) Dirichlet boundary condition
  will be used */
  BCtype = "DDDD";

  /* Setting the values of the boundary function G(x,y) that is equal to
  the TRUE solution in the mesh points laying on Dirichlet boundaries */
  for(iy=0;iy<=ny;iy++)
  {
    yi=hy*iy/ly;
    bd_ax[iy]=yi*yi*yi*yi;
    bd_bx[iy]=1.0E0-6.0E0*yi*yi+yi*yi*yi*yi;
  }
  for(ix=0;ix<=nx;ix++)
  {
    xi=hx*ix/lx;
    bd_ay[ix]=xi*xi*xi*xi;
    bd_by[ix]=1.0E0-6.0E0*xi*xi+xi*xi*xi*xi;
  }

  /* Initializing ipar array to make it free from garbage */
  for(i=0;i<128;i++)
  {
    ipar[i]=0;
  }

  /* Initializing simple data structures of Poisson Library for 2D Laplace Solver */
  s_init_Helmholtz_2D(&ax, &bx, &ay, &by, &nx, &ny, BCtype, &q, ipar, spar, &stat);
    if (stat!=0){ 
		error = 1;
		goto end;
	}

  /* Initializing complex data structures of Poisson Library for 2D Laplace Solver
  NOTE: Right-hand side f may be altered after the Commit step. If you want
  to keep it, you should save it in another memory location! */
  s_commit_Helmholtz_2D(f, bd_ax, bd_bx, bd_ay, bd_by, &xhandle, ipar, spar, &stat);
    if (stat!=0){
		error = 1;
		goto end;
	}
  /* Computing the approximate solution of 2D Laplace problem
  NOTE: Boundary data stored in the arrays bd_ax, bd_bx, bd_ay, bd_by
  should not be changed between the Commit step and the subsequent call to
  the Solver routine! Otherwise the results may be wrong. */
  s_Helmholtz_2D(f, bd_ax, bd_bx, bd_ay, bd_by, &xhandle, ipar, spar, &stat);
    if (stat!=0){
		error = 1;
		goto end;
	}
  /* Cleaning the memory used by xhandle */
  free_Helmholtz_2D(&xhandle, ipar, &stat);
    if (stat!=0){
		error = 1;
		goto end;
	}
  /* Now we can use xhandle to solve another 2D Laplace problem */

  /* Printing the results */
  printf("The number of mesh intervals in x-direction is nx=%d\n", nx);
  printf("The number of mesh intervals in y-direction is ny=%d\n\n", ny);

  /* Watching the error along the line x=hx */
  ix=1;
  c1=0.0;
  for(iy=0;iy<=ny;iy++)
  {
    printf("In the mesh point (%5.3f,%5.3f) ", ix*hx, iy*hy);
    printf("the error between the computed and the true solution ");
    printf("is equal to %10.3e\n", f[ix+iy*(nx+1)]-u[ix+iy*(nx+1)]);
    if (c1<fabs(f[ix+iy*(nx+1)]-u[ix+iy*(nx+1)]))
        c1=fabs(f[ix+iy*(nx+1)]-u[ix+iy*(nx+1)]);
  }
  if (c1>5.0e-03)
  {
    printf("The computed solution seems to be inaccurate. ");
	error = 1;
    goto end;
  }

end:
  /* Free Intel(R) MKL memory if any was allocated */
	mkl_free (spar);
	mkl_free (f);
	mkl_free (u);
	mkl_free (bd_ax);
	mkl_free (bd_bx);
	mkl_free (bd_ay);
	mkl_free (bd_by);
  MKL_Free_Buffers();
  /* Failure message to print if something went wrong */
	if (mem_error == 1) 
	{
		printf ("| insufficient memory \n");
		return 1;
	}


	if(error != 0)
	{
		 printf("\nSingle precision 2D Laplace example FAILED to compute ");
         printf("the solution...\n");
         return 1;
	}
  /* Success message to print if everything is OK */
  printf("\n Single precision 2D Laplace example has successfully PASSED\n");
  printf(" through all steps of computation!\n");
  return 0;
  /* End of the example code */
}
