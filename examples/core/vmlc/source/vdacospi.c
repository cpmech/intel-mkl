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
!     vdAcospi Example Program Text
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

  dA[0]=-1.0000;
  dA[1]=-0.8888;
  dA[2]=-0.6666;
  dA[3]=-0.4444;
  dA[4]=-0.2222;
  dA[5]=0.1111;
  dA[6]=0.3333;
  dA[7]=0.5555;
  dA[8]=0.7777;
  dA[9]=1.0000;
  dB[0]=1.0000000000000000e+00;
  dB[1]=8.4846022570481983e-01;
  dB[2]=7.3225105783572431e-01;
  dB[3]=6.4658309627503141e-01;
  dB[4]=5.7132379176824188e-01;
  dB[5]=4.6456261320803288e-01;
  dB[6]=3.9183780591422523e-01;
  dB[7]=3.1252688641090914e-01;
  dB[8]=2.1638628176247157e-01;
  dB[9]=0.0000000000000000e+00;

  vdAcospi(vec_len,dA,dBha0);

  vmdAcospi(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAcospi(vec_len,dA,dBep2);

  vmdAcospi(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAcospi(vec_len,dA,dBla2);

  vmdAcospi(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAcospi(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAcospi and vmdAcospi in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAcospi and vmdAcospi in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAcospi and vmdAcospi in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAcospi test/example program\n\n");
  printf("           Argument                     vdAcospi\n");
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
