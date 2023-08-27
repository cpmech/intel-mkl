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
!    vdSqr  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  double dA[10],dB[10];
  double dBha0[10],dBha1[10],dBha2[10];
  double           dBla1[10],dBla2[10];
  double           dBep1[10],dBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  dA[0]=1.0000;
  dA[1]=8.6666;
  dA[2]=16.3333;
  dA[3]=24.0000;
  dA[4]=31.6666;
  dA[5]=39.3333;
  dA[6]=47.0000;
  dA[7]=54.6666;
  dA[8]=62.3333;
  dA[9]=70.0000;
  dB[0]=1.0000000000000000e+000;
  dB[1]=7.5109955560000017e+001;
  dB[2]=2.6677668889000006e+002;
  dB[3]=5.7600000000000000e+002;
  dB[4]=1.0027735555600000e+003;
  dB[5]=1.5471084888900000e+003;
  dB[6]=2.2090000000000000e+003;
  dB[7]=2.9884371555600001e+003;
  dB[8]=3.8854402888900004e+003;
  dB[9]=4.9000000000000000e+003;

  vdSqr(vec_len,dA,dBha0);

  vmdSqr(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdSqr(vec_len,dA,dBep2);

  vmdSqr(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdSqr(vec_len,dA,dBla2);

  vmdSqr(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdSqr(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdSqr and vmdSqr in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdSqr and vmdSqr in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdSqr and vmdSqr in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdSqr test/example program\n\n");
  printf("           Argument                     vdSqr\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e\n",dA[i],dBha0[i]);
    CurRMS=drelerr(dB[i],dBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  if(MaxRMS>=1e-14) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  return 0;
}
