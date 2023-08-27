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
!     vdExp10 Example Program Text
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

  dA[0]=-17.1111;
  dA[1]=-13.2222;
  dA[2]=-9.3333;
  dA[3]=-5.4444;
  dA[4]=-1.5555;
  dA[5]=2.5555;
  dA[6]=6.4444;
  dA[7]=10.3333;
  dA[8]=14.2222;
  dA[9]=18.1111;
  dB[0]=7.7428349191245871e-18;
  dB[1]=5.9951492584815048e-14;
  dB[2]=4.6419451023934653e-10;
  dB[3]=3.5941814631471479e-06;
  dB[4]=2.7829153738526048e-02;
  dB[5]=3.5933539675538970e+02;
  dB[6]=2.7822746576751219e+06;
  dB[7]=2.1542693374042339e+10;
  dB[8]=1.6680151850852956e+14;
  dB[9]=1.2915166220708488e+18;

  vdExp10(vec_len,dA,dBha0);

  vmdExp10(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdExp10(vec_len,dA,dBep2);

  vmdExp10(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdExp10(vec_len,dA,dBla2);

  vmdExp10(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdExp10(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdExp10 and vmdExp10 in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdExp10 and vmdExp10 in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdExp10 and vmdExp10 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdExp10 test/example program\n\n");
  printf("           Argument                     vdExp10\n");
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
