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
!    vdExpm1  Example Program Text
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

  dA[0]=-17.0000;
  dA[1]=-13.1111;
  dA[2]=-9.2222;
  dA[3]=-5.3333;
  dA[4]=-1.4444;
  dA[5]=2.4444;
  dA[6]=6.3333;
  dA[7]=10.2222;
  dA[8]=14.1111;
  dA[9]=18.0000;
  dB[0]=-9.9999995860062285e-001;
  dB[1]=-9.9999797734590390e-001;
  dB[2]=-9.9990117895798236e-001;
  dB[3]=-9.9517188907181986e-001;
  dB[4]=-7.6411243335542101e-001;
  dB[5]=1.0523633344163436e+001;
  dB[6]=5.6201146947418135e+002;
  dB[7]=2.7506115619920700e+004;
  dB[8]=1.3439172871964260e+006;
  dB[9]=6.5659968137330510e+007;

  vdExpm1(vec_len,dA,dBha0);

  vmdExpm1(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdExpm1(vec_len,dA,dBep2);

  vmdExpm1(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdExpm1(vec_len,dA,dBla2);

  vmdExpm1(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdExpm1(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdExpm1 and vmdExpm1 in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdExpm1 and vmdExpm1 in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdExpm1 and vmdExpm1 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdExpm1 test/example program\n\n");
  printf("           Argument                     vdExpm1\n");
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
