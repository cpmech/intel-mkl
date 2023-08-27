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
!    vdInvCbrt  Example Program Text
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
  dB[0]=2.1544346900318834e+000;
  dB[1]=9.6546366855668919e-002;
  dB[2]=7.6630050381954806e-002;
  dB[3]=6.6942849394949100e-002;
  dB[4]=6.0821766532762715e-002;
  dB[5]=5.6462011167900103e-002;
  dB[6]=5.3132839904544968e-002;
  dB[7]=5.0471677903980341e-002;
  dB[8]=4.8274449115936070e-002;
  dB[9]=4.6415888336127795e-002;

  vdInvCbrt(vec_len,dA,dBha0);

  vmdInvCbrt(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdInvCbrt(vec_len,dA,dBep2);

  vmdInvCbrt(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdInvCbrt(vec_len,dA,dBla2);

  vmdInvCbrt(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdInvCbrt(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdInvCbrt and vmdInvCbrt in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdInvCbrt and vmdInvCbrt in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdInvCbrt and vmdInvCbrt in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdInvCbrt test/example program\n\n");
  printf("           Argument                     vdInvCbrt\n");
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
