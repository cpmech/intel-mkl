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
!    vdCosh  Example Program Text
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

  dA[0]=-7.0000;
  dA[1]=-5.4444;
  dA[2]=-3.8888;
  dA[3]=-2.3333;
  dA[4]=-0.7777;
  dA[5]=0.7777;
  dA[6]=2.3333;
  dA[7]=3.8888;
  dA[8]=5.4444;
  dA[9]=7.0000;
  dB[0]=5.4831703515521212e+002;
  dB[1]=1.1573134172748014e+002;
  dB[2]=2.4436349278419652e+001;
  dB[3]=5.2044449827109487e+000;
  dB[4]=1.3179611017029045e+000;
  dB[5]=1.3179611017029045e+000;
  dB[6]=5.2044449827109487e+000;
  dB[7]=2.4436349278419652e+001;
  dB[8]=1.1573134172748014e+002;
  dB[9]=5.4831703515521212e+002;

  vdCosh(vec_len,dA,dBha0);

  vmdCosh(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdCosh(vec_len,dA,dBep2);

  vmdCosh(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdCosh(vec_len,dA,dBla2);

  vmdCosh(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdCosh(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdCosh and vmdCosh in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdCosh and vmdCosh in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdCosh and vmdCosh in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdCosh test/example program\n\n");
  printf("           Argument                     vdCosh\n");
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
