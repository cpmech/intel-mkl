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
!    vsPow  Example Program Text
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

  fA[0]=0.1000;
  fA[1]=0.8666;
  fA[2]=1.6333;
  fA[3]=2.4000;
  fA[4]=3.1666;
  fA[5]=3.9333;
  fA[6]=4.7000;
  fA[7]=5.4666;
  fA[8]=6.2333;
  fA[9]=7.0000;
  fB[0]=7.9432823318248802e-001;
  fB[1]=8.8331105044955371e-001;
  fB[2]=2.2284382351152026e+000;
  fB[3]=8.1753632374188427e+000;
  fB[4]=3.8474983327516213e+001;
  fB[5]=2.1845299866537277e+002;
  fB[6]=1.4416496181341763e+003;
  fB[7]=1.0784631419538207e+004;
  fB[8]=8.9890987095794902e+004;
  fB[9]=8.2354300000000000e+005;

  vsPow(vec_len,fA,fA,fBha0);

  vmsPow(vec_len,fA,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsPow(vec_len,fA,fA,fBep2);

  vmsPow(vec_len,fA,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsPow(vec_len,fA,fA,fBla2);

  vmsPow(vec_len,fA,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsPow(vec_len,fA,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsPow and vmsPow in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsPow and vmsPow in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsPow and vmsPow in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsPow test/example program\n\n");
  printf("                     Arguments                               vsPow\n");
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
