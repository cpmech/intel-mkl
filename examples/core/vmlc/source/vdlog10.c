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
!    vdLog10  Example Program Text
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
  dA[1]=1111.1999;
  dA[2]=2222.2999;
  dA[3]=3333.3999;
  dA[4]=4444.5000;
  dA[5]=5555.6000;
  dA[6]=6666.7000;
  dA[7]=7777.8000;
  dA[8]=8888.9000;
  dA[9]=10000.0000;
  dB[0]=-1.0000000000000000e+000;
  dB[1]=3.0457921936461809e+000;
  dB[2]=3.3468026667229558e+000;
  dB[3]=3.5228874180545438e+000;
  dB[4]=3.6478229105357323e+000;
  dB[5]=3.7447309692386517e+000;
  dB[6]=3.8239109124112995e+000;
  dB[7]=3.8908567714145361e+000;
  dB[8]=3.9488480204203817e+000;
  dB[9]=4.0000000000000000e+000;

  vdLog10(vec_len,dA,dBha0);

  vmdLog10(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdLog10(vec_len,dA,dBep2);

  vmdLog10(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdLog10(vec_len,dA,dBla2);

  vmdLog10(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdLog10(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdLog10 and vmdLog10 in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdLog10 and vmdLog10 in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdLog10 and vmdLog10 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdLog10 test/example program\n\n");
  printf("           Argument                     vdLog10\n");
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
