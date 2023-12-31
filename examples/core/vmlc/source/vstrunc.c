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
!    vsTrunc  Example Program Text
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

  fA[0]=-2.0000;
  fA[1]=-1.5555;
  fA[2]=-1.1111;
  fA[3]=-0.6666;
  fA[4]=-0.2222;
  fA[5]=0.2222;
  fA[6]=0.6666;
  fA[7]=1.1111;
  fA[8]=1.5555;
  fA[9]=2.0000;
  fB[0]=-2.0000000000000000e+000;
  fB[1]=-1.0000000000000000e+000;
  fB[2]=-1.0000000000000000e+000;
  fB[3]=0.0000000000000000e+000;
  fB[4]=0.0000000000000000e+000;
  fB[5]=0.0000000000000000e+000;
  fB[6]=0.0000000000000000e+000;
  fB[7]=1.0000000000000000e+000;
  fB[8]=1.0000000000000000e+000;
  fB[9]=2.0000000000000000e+000;

  vsTrunc(vec_len,fA,fBha0);

  vmsTrunc(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsTrunc(vec_len,fA,fBep2);

  vmsTrunc(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsTrunc(vec_len,fA,fBla2);

  vmsTrunc(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsTrunc(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsTrunc and vmsTrunc in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsTrunc and vmsTrunc in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsTrunc and vmsTrunc in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsTrunc test/example program\n\n");
  printf("           Argument                     vsTrunc\n");
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
