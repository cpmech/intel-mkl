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
!    vsLGamma  Example Program Text
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

  fA[0]=  .5;
  fA[1]= 3.5;
  fA[2]= 6.5;
  fA[3]= 9.5;
  fA[4]=12.5;
  fA[5]=15.5;
  fA[6]=18.5;
  fA[7]=21.5;
  fA[8]=24.5;
  fA[9]=27.5;
  fB[0]=5.7236494292470009e-01;
  fB[1]=1.2009736023470742e+00;
  fB[2]=5.6625620598571415e+00;
  fB[3]=1.1689333420797268e+01;
  fB[4]=1.8734347511936446e+01;
  fB[5]=2.6536914491115614e+01;
  fB[6]=3.4943315776876818e+01;
  fB[7]=4.3851925860675161e+01;
  fB[8]=5.3190494526169265e+01;
  fB[9]=6.2904990828876504e+01;

  vsLGamma(vec_len,fA,fBha0);

  vmsLGamma(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsLGamma(vec_len,fA,fBep2);

  vmsLGamma(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsLGamma(vec_len,fA,fBla2);

  vmsLGamma(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsLGamma(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsLGamma and vmsLGamma in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsLGamma and vmsLGamma in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsLGamma and vmsLGamma in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsLGamma test/example program\n\n");
  printf("           Argument                     vsLGamma\n");
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
