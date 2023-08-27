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
!    vsAtan2  Example Program Text
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
  fB[0]=-2.3561944901923448e+000;
  fB[1]=-2.3561944901923448e+000;
  fB[2]=-2.3561944901923448e+000;
  fB[3]=-2.3561944901923448e+000;
  fB[4]=-2.3561944901923448e+000;
  fB[5]=7.8539816339744828e-001;
  fB[6]=7.8539816339744828e-001;
  fB[7]=7.8539816339744828e-001;
  fB[8]=7.8539816339744828e-001;
  fB[9]=7.8539816339744828e-001;

  vsAtan2(vec_len,fA,fA,fBha0);

  vmsAtan2(vec_len,fA,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsAtan2(vec_len,fA,fA,fBep2);

  vmsAtan2(vec_len,fA,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsAtan2(vec_len,fA,fA,fBla2);

  vmsAtan2(vec_len,fA,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsAtan2(vec_len,fA,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsAtan2 and vmsAtan2 in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsAtan2 and vmsAtan2 in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsAtan2 and vmsAtan2 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsAtan2 test/example program\n\n");
  printf("                     Arguments                               vsAtan2\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14f % 25.14e\n",fA[i],fA[i],fBha0[i]);
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
