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
!     vsLog2 Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  float fA[10],fB[10];
  float fBha0[10],fBha1[10],fBha2[10];
  float           fBla1[10],fBla2[10];
  float           fBep1[10],fBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  fA[0]=0.1111;
  fA[1]=1111.2222;
  fA[2]=2222.3333;
  fA[3]=3333.4444;
  fA[4]=4444.5555;
  fA[5]=5555.6666;
  fA[6]=6666.7777;
  fA[7]=7777.8888;
  fA[8]=8888.9999;
  fA[9]=9999.0000;
  fB[0]=-3.1700692176818848e+00;
  fB[1]=1.0117931365966797e+01;
  fB[2]=1.1117859840393066e+01;
  fB[3]=1.1702797889709473e+01;
  fB[4]=1.2117823600769043e+01;
  fB[5]=1.2439743995666504e+01;
  fB[6]=1.2702774047851562e+01;
  fB[7]=1.2925163269042969e+01;
  fB[8]=1.3117805480957031e+01;
  fB[9]=1.3287568092346191e+01;

  vsLog2(vec_len,fA,fBha0);

  vmsLog2(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsLog2(vec_len,fA,fBep2);

  vmsLog2(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsLog2(vec_len,fA,fBla2);

  vmsLog2(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsLog2(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsLog2 and vmsLog2 in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsLog2 and vmsLog2 in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsLog2 and vmsLog2 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsLog2 test/example program\n\n");
  printf("           Argument                     vsLog2\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e\n",fA[i],fBha0[i]);
    CurRMS=srelerr(fB[i],fBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  if(MaxRMS>=1e-5) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  return 0;
}
