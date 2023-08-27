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
!    vdAtanh  Example Program Text
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

  dA[0]=0.7500;
  dA[1]=0.7666;
  dA[2]=0.7833;
  dA[3]=0.8000;
  dA[4]=0.8166;
  dA[5]=0.8333;
  dA[6]=0.8500;
  dA[7]=0.8666;
  dA[8]=0.8833;
  dA[9]=0.9000;
  dB[0]=9.7295507452765662e-001;
  dB[1]=1.0120291772292880e+000;
  dB[2]=1.0538534754580771e+000;
  dB[3]=1.0986122886681098e+000;
  dB[4]=1.1465261706228744e+000;
  dB[5]=1.1988385554061158e+000;
  dB[6]=1.2561528119880574e+000;
  dB[7]=1.3192608698250616e+000;
  dB[8]=1.3905871484540955e+000;
  dB[9]=1.4722194895832204e+000;

  vdAtanh(vec_len,dA,dBha0);

  vmdAtanh(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAtanh(vec_len,dA,dBep2);

  vmdAtanh(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAtanh(vec_len,dA,dBla2);

  vmdAtanh(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAtanh(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAtanh and vmdAtanh in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAtanh and vmdAtanh in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAtanh and vmdAtanh in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAtanh test/example program\n\n");
  printf("           Argument                     vdAtanh\n");
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
