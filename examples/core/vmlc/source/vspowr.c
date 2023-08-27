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
!     vsPowr Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  float fA1[10],fA2[10],fB[10];
  float fBha0[10],fBha1[10],fBha2[10];
  float           fBla1[10],fBla2[10];
  float           fBep1[10],fBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  fA1[0]=0.1000;
  fA1[1]=0.8666;
  fA1[2]=1.6333;
  fA1[3]=2.4000;
  fA1[4]=3.1666;
  fA1[5]=3.9333;
  fA1[6]=4.7000;
  fA1[7]=5.4666;
  fA1[8]=6.2333;
  fA1[9]=7.0000;
  fA2[0]=-10.0000;
  fA2[1]=-7.7777;
  fA2[2]=-5.5555;
  fA2[3]=-3.3333;
  fA2[4]=-1.1111;
  fA2[5]=1.1111;
  fA2[6]=3.3333;
  fA2[7]=5.5555;
  fA2[8]=7.7777;
  fA2[9]=10.0000;
  fB[0]=9.9999989760000000e+09;
  fB[1]=3.0452833175659180e+00;
  fB[2]=6.5510682761669159e-02;
  fB[3]=5.4030846804380417e-02;
  fB[4]=2.7783754467964172e-01;
  fB[5]=4.5796737670898438e+00;
  fB[6]=1.7390168762207031e+02;
  fB[7]=1.2542625000000000e+04;
  fB[8]=1.5173246250000000e+06;
  fB[9]=2.8247526400000000e+08;

  vsPowr(vec_len,fA1,fA2,fBha0);

  vmsPowr(vec_len,fA1,fA2,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsPowr(vec_len,fA1,fA2,fBep2);

  vmsPowr(vec_len,fA1,fA2,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsPowr(vec_len,fA1,fA2,fBla2);

  vmsPowr(vec_len,fA1,fA2,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsPowr(vec_len,fA1,fA2,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsPowr and vmsPowr in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsPowr and vmsPowr in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsPowr and vmsPowr in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsPowr test/example program\n\n");
  printf("           Argument                     vsPowr\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f %25.14f % 25.14e\n",fA1[i],fA2[i],fBha0[i]);
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
