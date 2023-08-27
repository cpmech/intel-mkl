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
!    vdAtan  Example Program Text
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
  dB[0]=-1.5706963267952299e+000;
  dB[1]=-1.5706677553657480e+000;
  dB[2]=-1.5706163267950406e+000;
  dB[3]=-1.5704963268008967e+000;
  dB[4]=-1.5698963270288966e+000;
  dB[5]=1.5698963270288966e+000;
  dB[6]=1.5704963268008967e+000;
  dB[7]=1.5706163267950406e+000;
  dB[8]=1.5706677553657480e+000;
  dB[9]=1.5706963267952299e+000;

  vdAtan(vec_len,dA,dBha0);

  vmdAtan(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAtan(vec_len,dA,dBep2);

  vmdAtan(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAtan(vec_len,dA,dBla2);

  vmdAtan(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAtan(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAtan and vmdAtan in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAtan and vmdAtan in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAtan and vmdAtan in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAtan test/example program\n\n");
  printf("           Argument                     vdAtan\n");
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
