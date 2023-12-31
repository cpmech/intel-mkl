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
!    vdErf  Example Program Text
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

  dA[0]=1.0000;
  dA[1]=1.3333;
  dA[2]=1.6666;
  dA[3]=2.0000;
  dA[4]=2.3333;
  dA[5]=2.6666;
  dA[6]=3.0000;
  dA[7]=3.3333;
  dA[8]=3.6666;
  dA[9]=4.0000;
  dB[0]=8.4270079294971489e-001;
  dB[1]=9.4064720388873690e-001;
  dB[2]=9.8157319677988275e-001;
  dB[3]=9.9532226501895271e-001;
  dB[4]=9.9903240904150581e-001;
  dB[5]=9.9983749776098785e-001;
  dB[6]=9.9997790950300136e-001;
  dB[7]=9.9999757097033093e-001;
  dB[8]=9.9999978439673953e-001;
  dB[9]=9.9999998458274209e-001;

  vdErf(vec_len,dA,dBha0);

  vmdErf(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdErf(vec_len,dA,dBep2);

  vmdErf(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdErf(vec_len,dA,dBla2);

  vmdErf(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdErf(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdErf and vmdErf in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdErf and vmdErf in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdErf and vmdErf in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdErf test/example program\n\n");
  printf("           Argument                     vdErf\n");
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
