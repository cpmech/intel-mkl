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
!    vdAcos  Example Program Text
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

  dA[0]=-0.9000;
  dA[1]=-0.7000;
  dA[2]=-0.5000;
  dA[3]=-0.2999;
  dA[4]=-0.0999;
  dA[5]=0.0999;
  dA[6]=0.3000;
  dA[7]=0.5000;
  dA[8]=0.7000;
  dA[9]=0.9000;
  dB[0]=2.6905658417935308e+000;
  dB[1]=2.3461938234056494e+000;
  dB[2]=2.0943951023931957e+000;
  dB[3]=1.8753841540543150e+000;
  dB[4]=1.6708632446823510e+000;
  dB[5]=1.4707294089074423e+000;
  dB[6]=1.2661036727794992e+000;
  dB[7]=1.0471975511965979e+000;
  dB[8]=7.9539883018414359e-001;
  dB[9]=4.5102681179626236e-001;

  vdAcos(vec_len,dA,dBha0);

  vmdAcos(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAcos(vec_len,dA,dBep2);

  vmdAcos(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAcos(vec_len,dA,dBla2);

  vmdAcos(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAcos(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAcos and vmdAcos in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAcos and vmdAcos in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAcos and vmdAcos in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAcos test/example program\n\n");
  printf("           Argument                     vdAcos\n");
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
