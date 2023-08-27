/*******************************************************************************
* Copyright 2001-2019 Intel Corporation.
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
!     vdNextAfter Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  double dA1[10],dA2[10],dB[10];
  double dBha0[10],dBha1[10],dBha2[10];
  double           dBla1[10],dBla2[10];
  double           dBep1[10],dBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  dA1[0]=0.1000;
  dA1[1]=0.8666;
  dA1[2]=1.6333;
  dA1[3]=2.4000;
  dA1[4]=3.1666;
  dA1[5]=3.9333;
  dA1[6]=4.7000;
  dA1[7]=5.4666;
  dA1[8]=6.2333;
  dA1[9]=7.0000;
  dA2[0]=-10.0000;
  dA2[1]=-7.7777;
  dA2[2]=-5.5555;
  dA2[3]=-3.3333;
  dA2[4]=-1.1111;
  dA2[5]=1.1111;
  dA2[6]=3.3333;
  dA2[7]=5.5555;
  dA2[8]=7.7777;
  dA2[9]=10.0000;
  dB[0]=9.9999999999999992e-02;
  dB[1]=8.6659999999999993e-01;
  dB[2]=1.6332999999999998e+00;
  dB[3]=2.3999999999999995e+00;
  dB[4]=3.1665999999999994e+00;
  dB[5]=3.9332999999999996e+00;
  dB[6]=4.6999999999999993e+00;
  dB[7]=5.4666000000000006e+00;
  dB[8]=6.2333000000000007e+00;
  dB[9]=7.0000000000000009e+00;

  vdNextAfter(vec_len,dA1,dA2,dBha0);

  vmdNextAfter(vec_len,dA1,dA2,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdNextAfter(vec_len,dA1,dA2,dBep2);

  vmdNextAfter(vec_len,dA1,dA2,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdNextAfter(vec_len,dA1,dA2,dBla2);

  vmdNextAfter(vec_len,dA1,dA2,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdNextAfter(vec_len,dA1,dA2,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdNextAfter and vmdNextAfter in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdNextAfter and vmdNextAfter in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdNextAfter and vmdNextAfter in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdNextAfter test/example program\n\n");
  printf("           Argument                     vdNextAfter\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f %25.14f % 25.14e\n",dA1[i],dA2[i],dBha0[i]);
    CurRMS=drelerr(dB[i],dBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  if(MaxRMS>=1e-14) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  return 0;
}
