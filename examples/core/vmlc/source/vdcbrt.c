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
!    vdCbrt  Example Program Text
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

  dA[0]=0.0000;
  dA[1]=1111.1111;
  dA[2]=2222.2222;
  dA[3]=3333.3333;
  dA[4]=4444.4444;
  dA[5]=5555.5555;
  dA[6]=6666.6666;
  dA[7]=7777.7777;
  dA[8]=8888.8888;
  dA[9]=10000.0000;
  dB[0]=0.0000000000000000e+000;
  dB[1]=1.0357441651988058e+001;
  dB[2]=1.3049558760397682e+001;
  dB[3]=1.4938015772063830e+001;
  dB[4]=1.6441413774065087e+001;
  dB[5]=1.7710976094006931e+001;
  dB[6]=1.8820720514884833e+001;
  dB[7]=1.9813073109833521e+001;
  dB[8]=2.0714883303976116e+001;
  dB[9]=2.1544346900318835e+001;

  vdCbrt(vec_len,dA,dBha0);

  vmdCbrt(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdCbrt(vec_len,dA,dBep2);

  vmdCbrt(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdCbrt(vec_len,dA,dBla2);

  vmdCbrt(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdCbrt(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdCbrt and vmdCbrt in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdCbrt and vmdCbrt in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdCbrt and vmdCbrt in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdCbrt test/example program\n\n");
  printf("           Argument                     vdCbrt\n");
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
