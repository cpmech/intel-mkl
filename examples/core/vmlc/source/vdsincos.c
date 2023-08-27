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
!    vdSinCos  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  double dA[10],dB[10],dC[10];
  double dBha0[10],dBha1[10],dBha2[10];
  double           dBla1[10],dBla2[10];
  double           dBep1[10],dBep2[10];
  double dCha0[10],dCha1[10],dCha2[10];
  double           dCla1[10],dCla2[10];
  double           dCep1[10],dCep2[10];
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
  dB[0]=3.0561438888825215e-001;
  dB[1]=7.2132276994528466e-001;
  dB[2]=-9.3899224902885137e-001;
  dB[3]=1.0330988307550266e-001;
  dB[4]=8.4826444690664649e-001;
  dB[5]=-8.4826444690664649e-001;
  dB[6]=-1.0330988307550266e-001;
  dB[7]=9.3899224902885137e-001;
  dB[8]=-7.2132276994528466e-001;
  dB[9]=-3.0561438888825215e-001;
  dC[0]=-9.5215536825901481e-001;
  dC[1]=6.9259906263181004e-001;
  dC[2]=3.4393830299014322e-001;
  dC[3]=-9.9464921859866051e-001;
  dC[4]=5.2957287328011915e-001;
  dC[5]=5.2957287328011915e-001;
  dC[6]=-9.9464921859866051e-001;
  dC[7]=3.4393830299014322e-001;
  dC[8]=6.9259906263181004e-001;
  dC[9]=-9.5215536825901481e-001;

  vdSinCos(vec_len,dA,dBha0,dCha0);

  vmdSinCos(vec_len,dA,dBep1,dCep1,VML_EP);

  vmlSetMode(VML_EP);
  vdSinCos(vec_len,dA,dBep2,dCep2);

  vmdSinCos(vec_len,dA,dBla1,dCla1,VML_LA);

  vmlSetMode(VML_LA);
  vdSinCos(vec_len,dA,dBla2,dCla2);

  vmdSinCos(vec_len,dA,dBha1,dCha1,VML_HA);

  vmlSetMode(VML_HA);
  vdSinCos(vec_len,dA,dBha2,dCha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dCha0[i]!=dCha1[i] || dBha1[i]!=dBha2[i] || dCha1[i]!=dCha2[i]) {
      printf("Error! Difference between vdSinCos and vmdSinCos in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i] || dCla1[i]!=dCla2[i]) {
      printf("Error! Difference between vdSinCos and vmdSinCos in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i] || dCep1[i]!=dCep2[i]) {
      printf("Error! Difference between vdSinCos and vmdSinCos in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdSinCos test/example program\n\n");
  printf("           Argument                            vdSinCos\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e % 25.14e\n",dA[i],dBha0[i],dCha0[i]);
    CurRMS=drelerr(dB[i],dBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
    CurRMS=drelerr(dC[i],dCha0[i]);
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
