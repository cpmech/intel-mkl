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
!     vdLog2 Example Program Text
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

  dA[0]=0.1111;
  dA[1]=1111.2222;
  dA[2]=2222.3333;
  dA[3]=3333.4444;
  dA[4]=4444.5555;
  dA[5]=5555.6666;
  dA[6]=6666.7777;
  dA[7]=7777.8888;
  dA[8]=8888.9999;
  dA[9]=9999.0000;
  dB[0]=-3.1700692781603572e+00;
  dB[1]=1.0117931611547215e+01;
  dB[2]=1.1117859489416530e+01;
  dB[3]=1.1702797948626218e+01;
  dB[4]=1.2117823426999088e+01;
  dB[5]=1.2439744309294788e+01;
  dB[6]=1.2702773906714107e+01;
  dB[7]=1.2925162893458976e+01;
  dB[8]=1.3117805395452322e+01;
  dB[9]=1.3287568102831404e+01;

  vdLog2(vec_len,dA,dBha0);

  vmdLog2(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdLog2(vec_len,dA,dBep2);

  vmdLog2(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdLog2(vec_len,dA,dBla2);

  vmdLog2(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdLog2(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdLog2 and vmdLog2 in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdLog2 and vmdLog2 in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdLog2 and vmdLog2 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdLog2 test/example program\n\n");
  printf("           Argument                     vdLog2\n");
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
