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
!     vdCopySign Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  double dA1[10],dA2[10],dB[10];
  double dBha0[10],dBha1[10],dBha2[10];
  double           dBla1[10],dBla2[10];
  double           dBep1[10],dBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  dA1[0]=0.1000;
  dA1[1]=0.8666;
  dA1[2]=1.6333;
  dA1[3]=2.4000;
  dA1[4]=3.1666;
  dA1[5]=3.9333;
  dA1[6]=4.7000;
  dA1[7]=5.4666;
  dA1[8]=6.2333;
  dA1[9]=7.0000;
  dA2[0]=-10.0000;
  dA2[1]=-7.7777;
  dA2[2]=-5.5555;
  dA2[3]=-3.3333;
  dA2[4]=-1.1111;
  dA2[5]=1.1111;
  dA2[6]=3.3333;
  dA2[7]=5.5555;
  dA2[8]=7.7777;
  dA2[9]=10.0000;
  dB[0]=-1.0000000000000001e-01;
  dB[1]=-8.6660000000000004e-01;
  dB[2]=-1.6333000000000000e+00;
  dB[3]=-2.3999999999999999e+00;
  dB[4]=-3.1665999999999999e+00;
  dB[5]=3.9333000000000000e+00;
  dB[6]=4.7000000000000002e+00;
  dB[7]=5.4665999999999997e+00;
  dB[8]=6.2332999999999998e+00;
  dB[9]=7.0000000000000000e+00;

  vdCopySign(vec_len,dA1,dA2,dBha0);

  vmdCopySign(vec_len,dA1,dA2,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdCopySign(vec_len,dA1,dA2,dBep2);

  vmdCopySign(vec_len,dA1,dA2,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdCopySign(vec_len,dA1,dA2,dBla2);

  vmdCopySign(vec_len,dA1,dA2,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdCopySign(vec_len,dA1,dA2,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdCopySign and vmdCopySign in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdCopySign and vmdCopySign in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdCopySign and vmdCopySign in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdCopySign test/example program\n\n");
  printf("           Argument                     vdCopySign\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f %25.14f % 25.14e\n",dA1[i],dA2[i],dBha0[i]);
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
