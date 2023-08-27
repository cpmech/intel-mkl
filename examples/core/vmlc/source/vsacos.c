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
!    vsAcos  Example Program Text
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

  fA[0]=-0.9000;
  fA[1]=-0.7000;
  fA[2]=-0.5000;
  fA[3]=-0.2999;
  fA[4]=-0.0999;
  fA[5]=0.0999;
  fA[6]=0.3000;
  fA[7]=0.5000;
  fA[8]=0.7000;
  fA[9]=0.9000;
  fB[0]=2.6905657870965607e+000;
  fB[1]=2.3461938067130106e+000;
  fB[2]=2.0943951023931957e+000;
  fB[3]=1.8753841491558372e+000;
  fB[4]=1.6708632444786764e+000;
  fB[5]=1.4707294091111169e+000;
  fB[6]=1.2661036602829701e+000;
  fB[7]=1.0471975511965979e+000;
  fB[8]=7.9539884687678286e-001;
  fB[9]=4.5102686649323265e-001;

  vsAcos(vec_len,fA,fBha0);

  vmsAcos(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsAcos(vec_len,fA,fBep2);

  vmsAcos(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsAcos(vec_len,fA,fBla2);

  vmsAcos(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsAcos(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsAcos and vmsAcos in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsAcos and vmsAcos in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsAcos and vmsAcos in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsAcos test/example program\n\n");
  printf("           Argument                     vsAcos\n");
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
