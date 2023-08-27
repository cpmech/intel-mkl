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
!    vdHypot  Example Program Text
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

  dA[0]=1.0009;
  dA[1]=1112.0008;
  dA[2]=2223.0007;
  dA[3]=3334.0006;
  dA[4]=4445.0005;
  dA[5]=5556.0004;
  dA[6]=6667.0003;
  dA[7]=7778.0002;
  dA[8]=8889.0001;
  dA[9]=10000.0000;
  dB[0]=1.4154863545792307e+000;
  dB[1]=1.5726066127297315e+003;
  dB[2]=3.1437977391048839e+003;
  dB[3]=4.7149888654800361e+003;
  dB[4]=6.2861799918551887e+003;
  dB[5]=7.8573711182303405e+003;
  dB[6]=9.4285622446054931e+003;
  dB[7]=1.0999753370980647e+004;
  dB[8]=1.2570944497355797e+004;
  dB[9]=1.4142135623730950e+004;

  vdHypot(vec_len,dA,dA,dBha0);

  vmdHypot(vec_len,dA,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdHypot(vec_len,dA,dA,dBep2);

  vmdHypot(vec_len,dA,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdHypot(vec_len,dA,dA,dBla2);

  vmdHypot(vec_len,dA,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdHypot(vec_len,dA,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdHypot and vmdHypot in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdHypot and vmdHypot in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdHypot and vmdHypot in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdHypot test/example program\n\n");
  printf("                     Arguments                               vdHypot\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14f % 25.14e\n",dA[i],dA[i],dBha0[i]);
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
