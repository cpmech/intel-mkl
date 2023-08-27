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
!     vsLogb Example Program Text
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

  fA[0]=-17.1111;
  fA[1]=-13.2222;
  fA[2]=-9.3333;
  fA[3]=-5.4444;
  fA[4]=-1.5555;
  fA[5]=2.5555;
  fA[6]=6.4444;
  fA[7]=10.3333;
  fA[8]=14.2222;
  fA[9]=18.1111;
  fB[0]=4.0000000000000000e+00;
  fB[1]=3.0000000000000000e+00;
  fB[2]=3.0000000000000000e+00;
  fB[3]=2.0000000000000000e+00;
  fB[4]=0.0000000000000000e+00;
  fB[5]=1.0000000000000000e+00;
  fB[6]=2.0000000000000000e+00;
  fB[7]=3.0000000000000000e+00;
  fB[8]=3.0000000000000000e+00;
  fB[9]=4.0000000000000000e+00;

  vsLogb(vec_len,fA,fBha0);

  vmsLogb(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsLogb(vec_len,fA,fBep2);

  vmsLogb(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsLogb(vec_len,fA,fBla2);

  vmsLogb(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsLogb(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsLogb and vmsLogb in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsLogb and vmsLogb in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsLogb and vmsLogb in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsLogb test/example program\n\n");
  printf("           Argument                     vsLogb\n");
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
