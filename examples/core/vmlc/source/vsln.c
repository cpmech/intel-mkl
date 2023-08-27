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
!    vsLn  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  float fA[10],fB[10];
  float fBha0[10],fBha1[10],fBha2[10];
  float           fBla1[10],fBla2[10];
  float           fBep1[10],fBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  fA[0]=0.1000;
  fA[1]=1111.2000;
  fA[2]=2222.2998;
  fA[3]=3333.3999;
  fA[4]=4444.5000;
  fA[5]=5555.6001;
  fA[6]=6666.7002;
  fA[7]=7777.7998;
  fA[8]=8888.9004;
  fA[9]=10000.0000;
  fB[0]=-2.3025850780928847e+000;
  fB[1]=7.0131957474983357e+000;
  fB[2]=7.7062978866998701e+000;
  fB[3]=8.1117480538117857e+000;
  fB[4]=8.3994226556817289e+000;
  fB[5]=8.6225617246200486e+000;
  fB[6]=8.8048802931522463e+000;
  fB[7]=8.9590287757225173e+000;
  fB[8]=9.0925586302642749e+000;
  fB[9]=9.2103403719761836e+000;

  vsLn(vec_len,fA,fBha0);

  vmsLn(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsLn(vec_len,fA,fBep2);

  vmsLn(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsLn(vec_len,fA,fBla2);

  vmsLn(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsLn(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsLn and vmsLn in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsLn and vmsLn in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsLn and vmsLn in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsLn test/example program\n\n");
  printf("           Argument                     vsLn\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e\n",fA[i],fBha0[i]);
    CurRMS=srelerr(fB[i],fBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  if(MaxRMS>=1e-5) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  return 0;
}
