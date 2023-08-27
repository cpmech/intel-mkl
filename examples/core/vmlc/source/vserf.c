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
!    vsErf  Example Program Text
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

  fA[0]=1.0000;
  fA[1]=1.3333;
  fA[2]=1.6666;
  fA[3]=2.0000;
  fA[4]=2.3333;
  fA[5]=2.6666;
  fA[6]=3.0000;
  fA[7]=3.3333;
  fA[8]=3.6666;
  fA[9]=4.0000;
  fB[0]=8.4270079294971489e-001;
  fB[1]=9.4064720283376069e-001;
  fB[2]=9.8157319600357118e-001;
  fB[3]=9.9532226501895271e-001;
  fB[4]=9.9903240959575701e-001;
  fB[5]=9.9983749775079844e-001;
  fB[6]=9.9997790950300136e-001;
  fB[7]=9.9999757097224840e-001;
  fB[8]=9.9999978439672144e-001;
  fB[9]=9.9999998458274209e-001;

  vsErf(vec_len,fA,fBha0);

  vmsErf(vec_len,fA,fBep1,VML_EP);

  vmlSetMode(VML_EP);
  vsErf(vec_len,fA,fBep2);

  vmsErf(vec_len,fA,fBla1,VML_LA);

  vmlSetMode(VML_LA);
  vsErf(vec_len,fA,fBla2);

  vmsErf(vec_len,fA,fBha1,VML_HA);

  vmlSetMode(VML_HA);
  vsErf(vec_len,fA,fBha2);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsErf and vmsErf in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsErf and vmsErf in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsErf and vmsErf in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsErf test/example program\n\n");
  printf("           Argument                     vsErf\n");
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
