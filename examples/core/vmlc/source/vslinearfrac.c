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
!    vsLinearFrac  Example Program Text
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
  float fScale, fShift;
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  fA[0]=-10000.0000;
  fA[1]=-7777.7778;
  fA[2]=-5555.5557;
  fA[3]=-3333.3333;
  fA[4]=-1111.1111;
  fA[5]=1111.1111;
  fA[6]=3333.3333;
  fA[7]=5555.5557;
  fA[8]=7777.7778;
  fA[9]=10000.0000;
  fB[0]=1.0000000000000000e+000;
  fB[1]=1.0000000000000000e+000;
  fB[2]=1.0000000000000000e+000;
  fB[3]=1.0000000000000000e+000;
  fB[4]=1.0000000000000000e+000;
  fB[5]=1.0000000000000000e+000;
  fB[6]=1.0000000000000000e+000;
  fB[7]=1.0000000000000000e+000;
  fB[8]=1.0000000000000000e+000;
  fB[9]=1.0000000000000000e+000;
  fScale = 1.0000000000000000e+000;
  fShift = 0.0000000000000000e+000;

  vsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBha0);

  vmsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBep2);

  vmsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBla2);

  vmsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsLinearFrac(vec_len,fA,fA,fScale,fShift,fScale,fShift,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsLinearFrac and vmsLinearFrac in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsLinearFrac and vmsLinearFrac in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsLinearFrac and vmsLinearFrac in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsLinearFrac test/example program\n\n");
  printf("Scalar Parameters: ScaleA = ScaleB = %.4f, ShiftA = ShiftB = %.4f\n\n", fScale, fShift);
  printf("                     Arguments                               vsLinearFrac\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14f % 25.14e\n",fA[i],fA[i],fBha0[i]);
    CurRMS=srelerr(fB[i],fBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  if(MaxRMS>=1e-3) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  return 0;
}
