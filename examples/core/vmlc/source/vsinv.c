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
!    vsInv  Example Program Text
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
  fB[0]=-1.0000000000000000e-004;
  fB[1]=-1.2857142767458546e-004;
  fB[2]=-1.7999999648437507e-004;
  fB[3]=-3.0000000732421895e-004;
  fB[4]=-9.0000002197265674e-004;
  fB[5]=9.0000002197265674e-004;
  fB[6]=3.0000000732421895e-004;
  fB[7]=1.7999999648437507e-004;
  fB[8]=1.2857142767458546e-004;
  fB[9]=1.0000000000000000e-004;

  vsInv(vec_len,fA,fBha0);

  vmsInv(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsInv(vec_len,fA,fBep2);

  vmsInv(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsInv(vec_len,fA,fBla2);

  vmsInv(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsInv(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsInv and vmsInv in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsInv and vmsInv in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsInv and vmsInv in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsInv test/example program\n\n");
  printf("           Argument                     vsInv\n");
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
