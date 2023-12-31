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
!    vdAbs  Example Program Text
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

  dA[0]=-1000.0000;
  dA[1]=-777.7777;
  dA[2]=-555.5555;
  dA[3]=-333.3333;
  dA[4]=-111.1111;
  dA[5]=111.1111;
  dA[6]=333.3333;
  dA[7]=555.5555;
  dA[8]=777.7777;
  dA[9]=1000.0000;
  dB[0]=1.0000000000000000e+003;
  dB[1]=7.7777769999999998e+002;
  dB[2]=5.5555550000000005e+002;
  dB[3]=3.3333330000000001e+002;
  dB[4]=1.1111109999999999e+002;
  dB[5]=1.1111109999999999e+002;
  dB[6]=3.3333330000000001e+002;
  dB[7]=5.5555550000000005e+002;
  dB[8]=7.7777769999999998e+002;
  dB[9]=1.0000000000000000e+003;

  vdAbs(vec_len,dA,dBha0);

  vmdAbs(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAbs(vec_len,dA,dBep2);

  vmdAbs(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAbs(vec_len,dA,dBla2);

  vmdAbs(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAbs(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAbs and vmdAbs in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAbs and vmdAbs in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAbs and vmdAbs in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAbs test/example program\n\n");
  printf("           Argument                     vdAbs\n");
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
