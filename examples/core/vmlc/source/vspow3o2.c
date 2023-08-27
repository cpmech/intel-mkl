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
!    vsPow3o2  Example Program Text
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

  fA[0]=1.0000;
  fA[1]=1.6666;
  fA[2]=2.3333;
  fA[3]=3.0000;
  fA[4]=3.6666;
  fA[5]=4.3333;
  fA[6]=5.0000;
  fA[7]=5.6666;
  fA[8]=6.3333;
  fA[9]=7.0000;
  fB[0]=1.0000000000000000e+000;
  fB[1]=2.1515282949835584e+000;
  fB[2]=3.5641494249995125e+000;
  fB[3]=5.1961524227066320e+000;
  fB[4]=7.0209406072206448e+000;
  fB[5]=9.0204489362114408e+000;
  fB[6]=1.1180339887498949e+001;
  fB[7]=1.3489127574374065e+001;
  fB[8]=1.5938413962064837e+001;
  fB[9]=1.8520259177452136e+001;

  vsPow3o2(vec_len,fA,fBha0);

  vmsPow3o2(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsPow3o2(vec_len,fA,fBep2);

  vmsPow3o2(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsPow3o2(vec_len,fA,fBla2);

  vmsPow3o2(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsPow3o2(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsPow3o2 and vmsPow3o2 in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsPow3o2 and vmsPow3o2 in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsPow3o2 and vmsPow3o2 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsPow3o2 test/example program\n\n");
  printf("           Argument                     vsPow3o2\n");
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
