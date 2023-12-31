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
!    vdLn  Example Program Text
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
  dB[0]=-2.3025850929940455e+000;
  dB[1]=7.0131957014473292e+000;
  dB[2]=7.7062979295889971e+000;
  dB[3]=8.1117480531086752e+000;
  dB[4]=8.3994226556817289e+000;
  dB[5]=8.6225617070420633e+000;
  dB[6]=8.8048802638555177e+000;
  dB[7]=8.9590288008340515e+000;
  dB[8]=9.0925585863190186e+000;
  dB[9]=9.2103403719761836e+000;

  vdLn(vec_len,dA,dBha0);

  vmdLn(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdLn(vec_len,dA,dBep2);

  vmdLn(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdLn(vec_len,dA,dBla2);

  vmdLn(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdLn(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdLn and vmdLn in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdLn and vmdLn in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdLn and vmdLn in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdLn test/example program\n\n");
  printf("           Argument                     vdLn\n");
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
