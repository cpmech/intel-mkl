/*******************************************************************************
* Copyright 2001-2020 Intel Corporation.
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

#define INCA 3
#define INCB 5

int main()
{
  float fA[10],fB[10];
  float fBha0[10],fBha1[10],fBha2[10];
  float           fBla1[10],fBla2[10];
  float           fBep1[10],fBep2[10];
  float CurRMS,MaxRMS=0.0;

  float fA_I[10*INCA],fB_I[10*INCB];
  float fBha0_I[10*INCB],fBha1_I[10*INCB],fBha2_I[10*INCB];
  float                  fBla1_I[10*INCB],fBla2_I[10*INCB];
  float                  fBep1_I[10*INCB],fBep2_I[10*INCB];
  float CurRMS_I,MaxRMS_I=0.0;
  MKL_INT inca=INCA,incb=INCB;

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

  for(i=0;i<10;i++) {
    fA_I[i*inca]=fA[i];
    fB_I[i*incb]=fB[i];
  }

  vsLGamma(vec_len,fA,fBha0);
  vsLGammaI(vec_len,fA_I,inca,fBha0_I,incb);

  vmsLGamma(vec_len,fA,fBep1,VML_EP);
  vmsLGammaI(vec_len,fA_I,inca,fBep1_I,incb,VML_EP);

  vmlSetMode(VML_EP);
  vsLGamma(vec_len,fA,fBep2);
  vsLGammaI(vec_len,fA_I,inca,fBep2_I,incb);

  vmsLGamma(vec_len,fA,fBla1,VML_LA);
  vmsLGammaI(vec_len,fA_I,inca,fBla1_I,incb,VML_LA);

  vmlSetMode(VML_LA);
  vsLGamma(vec_len,fA,fBla2);
  vsLGammaI(vec_len,fA_I,inca,fBla2_I,incb);

  vmsLGamma(vec_len,fA,fBha1,VML_HA);
  vmsLGammaI(vec_len,fA_I,inca,fBha1_I,incb,VML_HA);

  vmlSetMode(VML_HA);
  vsLGamma(vec_len,fA,fBha2);
  vsLGammaI(vec_len,fA_I,inca,fBha2_I,incb);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsLGamma and vmsLGamma in VML_HA mode detected.\n");
      return 1;
    }

    if(fBha0_I[i*incb]!=fBha1_I[i*incb] || fBha1_I[i*incb]!=fBha2_I[i*incb]) {
      printf("Error! Difference between vsLGammaI and vmsLGammaI in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsLGamma and vmsLGamma in VML_LA mode detected.\n");
      return 1;
    }

    if(fBla1_I[i*incb]!=fBla2_I[i*incb]) {
      printf("Error! Difference between vsLGammaI and vmsLGammaI in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsLGamma and vmsLGamma in VML_EP mode detected.\n");
      return 1;
    }

    if(fBep1_I[i*incb]!=fBep2_I[i*incb]) {
      printf("Error! Difference between vsLGammaI and vmsLGammaI in VML_EP mode detected.\n");
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
  printf("vsLGammaI test/example program\n\n");
  printf("           Argument                     vsLGamma\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e\n",fA_I[i*inca],fBha0_I[i*incb]);
    CurRMS_I=srelerr(fB_I[i*incb],fBha0_I[i*incb]);
    if(CurRMS_I>MaxRMS_I) MaxRMS_I=CurRMS_I;
  }
  printf("\n");
  if(MaxRMS>=1e-5) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  printf("\n");

  if(MaxRMS_I>=1e-5) {
    printf("Error! Relative strided accuracy is %.16f\n",MaxRMS_I);
    return 1;
  }
  else {
    printf("Relative strided accuracy is %.16f\n",MaxRMS_I);
  }
  return 0;
}
