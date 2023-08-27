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
!    vdLinearFrac  Example Program Text
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
  double dScale, dShift;
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  dA[0]=-10000.0000;
  dA[1]=-7777.7777;
  dA[2]=-5555.5555;
  dA[3]=-3333.3333;
  dA[4]=-1111.1111;
  dA[5]=1111.1111;
  dA[6]=3333.3333;
  dA[7]=5555.5555;
  dA[8]=7777.7777;
  dA[9]=10000.0000;
  dB[0]=1.0000000000000000e+000;
  dB[1]=1.0000000000000000e+000;
  dB[2]=1.0000000000000000e+000;
  dB[3]=1.0000000000000000e+000;
  dB[4]=1.0000000000000000e+000;
  dB[5]=1.0000000000000000e+000;
  dB[6]=1.0000000000000000e+000;
  dB[7]=1.0000000000000000e+000;
  dB[8]=1.0000000000000000e+000;
  dB[9]=1.0000000000000000e+000;
  dScale = 1.0000000000000000e+000;
  dShift = 0.0000000000000000e+000;

  vdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBha0);

  vmdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBep2);

  vmdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBla2);

  vmdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdLinearFrac(vec_len,dA,dA,dScale,dShift,dScale,dShift,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdLinearFrac and vmdLinearFrac in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdLinearFrac and vmdLinearFrac in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdLinearFrac and vmdLinearFrac in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdLinearFrac test/example program\n\n");
  printf("Scalar Parameters: ScaleA = ScaleB = %.4f, ShiftA = ShiftB = %.4f\n\n", dScale, dShift);
  printf("                     Arguments                               vdLinearFrac\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14f % 25.14e\n",dA[i],dA[i],dBha0[i]);
    CurRMS=drelerr(dB[i],dBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  if(MaxRMS>=3e-8) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }
  return 0;
}
