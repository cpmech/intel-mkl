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
!    vsCdfNorm  Example Program Text
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

  fA[0]=-8.0000;
  fA[1]=-6.5555;
  fA[2]=-5.1111;
  fA[3]=-3.6666;
  fA[4]=-2.2222;
  fA[5]=-0.7777;
  fA[6]=0.6666;
  fA[7]=2.1111;
  fA[8]=3.5555;
  fA[9]=5.0000;
  fB[0]=6.22096057427178e-16;
  fB[1]=2.77278689399088e-11;
  fB[2]=1.60144022698396e-07;
  fB[3]=1.22898417236556e-04;
  fB[4]=1.31348990439007e-02;
  fB[5]=2.18372944048033e-01;
  fB[6]=7.47486161912039e-01;
  fB[7]=9.82618139490682e-01;
  fB[8]=9.99811369549446e-01;
  fB[9]=9.99999713348428e-01;

  vsCdfNorm(vec_len,fA,fBha0);

  vmsCdfNorm(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsCdfNorm(vec_len,fA,fBep2);

  vmsCdfNorm(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsCdfNorm(vec_len,fA,fBla2);

  vmsCdfNorm(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsCdfNorm(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsCdfNorm and vmsCdfNorm in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsCdfNorm and vmsCdfNorm in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsCdfNorm and vmsCdfNorm in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsCdfNorm test/example program\n\n");
  printf("           Argument                     vsCdfNorm\n");
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
