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
!    vdAcosh  Example Program Text
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

  dA[0]=3.5000;
  dA[1]=1114.2222;
  dA[2]=2224.9444;
  dA[3]=3335.6666;
  dA[4]=4446.3888;
  dA[5]=5557.1111;
  dA[6]=6667.8333;
  dA[7]=7778.5555;
  dA[8]=8889.2777;
  dA[9]=10000.0000;
  dB[0]=1.9248473002384139e+000;
  dB[1]=7.7090588411869394e+000;
  dB[2]=8.4006343355828150e+000;
  dB[3]=8.8055749765277476e+000;
  dB[4]=9.0929947080081401e+000;
  dB[5]=9.3159808383464178e+000;
  dB[6]=9.4981974184950921e+000;
  dB[7]=9.6522731079815856e+000;
  dB[8]=9.7857482540093379e+000;
  dB[9]=9.9034875500361288e+000;

  vdAcosh(vec_len,dA,dBha0);

  vmdAcosh(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAcosh(vec_len,dA,dBep2);

  vmdAcosh(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAcosh(vec_len,dA,dBla2);

  vmdAcosh(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAcosh(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAcosh and vmdAcosh in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAcosh and vmdAcosh in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAcosh and vmdAcosh in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAcosh test/example program\n\n");
  printf("           Argument                     vdAcosh\n");
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
