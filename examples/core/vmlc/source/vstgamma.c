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
!    vsTGamma  Example Program Text
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
  fB[0]=1.7724538509055160e+00;
  fB[1]=3.3233509704478426e+00;
  fB[2]=2.8788527781504436e+02;
  fB[3]=1.1929246199460901e+05;
  fB[4]=1.3684336546556586e+08;
  fB[5]=3.3483860987355646e+11;
  fB[6]=1.4986120533153361e+15;
  fB[7]=1.1082798113786904e+19;
  fB[8]=1.2599063430729375e+23;
  fB[9]=2.0858851927622669e+27;

  vsTGamma(vec_len,fA,fBha0);

  vmsTGamma(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsTGamma(vec_len,fA,fBep2);

  vmsTGamma(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsTGamma(vec_len,fA,fBla2);

  vmsTGamma(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsTGamma(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsTGamma and vmsTGamma in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsTGamma and vmsTGamma in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsTGamma and vmsTGamma in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsTGamma test/example program\n\n");
  printf("           Argument                     vsTGamma\n");
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
