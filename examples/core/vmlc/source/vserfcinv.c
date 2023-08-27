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
!    vsErfcInv  Example Program Text
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

  fA[0]=0.0001;
  fA[1]=0.2223;
  fA[2]=0.4445;
  fA[3]=0.6667;
  fA[4]=0.8889;
  fA[5]=1.1111;
  fA[6]=1.3333;
  fA[7]=1.5555;
  fA[8]=1.7777;
  fA[9]=1.9999;
  fB[0]= 2.75106391005276e+00;
  fB[1]= 8.62977907541907e-01;
  fB[2]= 5.40665442919061e-01;
  fB[3]= 3.04537776793446e-01;
  fB[4]= 9.87801723434816e-02;
  fB[5]=-9.87801190022983e-02;
  fB[6]=-3.04537776793446e-01;
  fB[7]=-5.40665478298228e-01;
  fB[8]=-8.62977796302805e-01;
  fB[9]=-2.75103543790861e+00;

  vsErfcInv(vec_len,fA,fBha0);

  vmsErfcInv(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsErfcInv(vec_len,fA,fBep2);

  vmsErfcInv(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsErfcInv(vec_len,fA,fBla2);

  vmsErfcInv(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsErfcInv(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsErfcInv and vmsErfcInv in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsErfcInv and vmsErfcInv in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsErfcInv and vmsErfcInv in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsErfcInv test/example program\n\n");
  printf("           Argument                     vsErfcInv\n");
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
