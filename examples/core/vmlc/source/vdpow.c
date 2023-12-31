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
!    vdPow  Example Program Text
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

  dA[0]=0.1000;
  dA[1]=0.8666;
  dA[2]=1.6333;
  dA[3]=2.4000;
  dA[4]=3.1666;
  dA[5]=3.9333;
  dA[6]=4.7000;
  dA[7]=5.4666;
  dA[8]=6.2333;
  dA[9]=7.0000;
  dB[0]=7.9432823472428149e-001;
  dB[1]=8.8331106784443691e-001;
  dB[2]=2.2284384118803935e+000;
  dB[3]=8.1753617751846335e+000;
  dB[4]=3.8474984243761270e+001;
  dB[5]=2.1845298918747244e+002;
  dB[6]=1.4416503186448467e+003;
  dB[7]=1.0784633129292892e+004;
  dB[8]=8.9890933918204668e+004;
  dB[9]=8.2354300000000000e+005;

  vdPow(vec_len,dA,dA,dBha0);

  vmdPow(vec_len,dA,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdPow(vec_len,dA,dA,dBep2);

  vmdPow(vec_len,dA,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdPow(vec_len,dA,dA,dBla2);

  vmdPow(vec_len,dA,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdPow(vec_len,dA,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdPow and vmdPow in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdPow and vmdPow in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdPow and vmdPow in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdPow test/example program\n\n");
  printf("                     Arguments                               vdPow\n");
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
