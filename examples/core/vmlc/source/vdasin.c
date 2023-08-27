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
!    vdAsin  Example Program Text
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

  dA[0]=-1.0000;
  dA[1]=-0.7777;
  dA[2]=-0.5555;
  dA[3]=-0.3333;
  dA[4]=-0.1111;
  dA[5]=0.1111;
  dA[6]=0.3333;
  dA[7]=0.5555;
  dA[8]=0.7777;
  dA[9]=1.0000;
  dB[0]=-1.5707963267948966e+000;
  dB[1]=-8.9099877367230484e-001;
  dB[2]=-5.8896415639709265e-001;
  dB[3]=-3.3980155433602333e-001;
  dB[4]=-1.1132983400806387e-001;
  dB[5]=1.1132983400806387e-001;
  dB[6]=3.3980155433602333e-001;
  dB[7]=5.8896415639709265e-001;
  dB[8]=8.9099877367230484e-001;
  dB[9]=1.5707963267948966e+000;

  vdAsin(vec_len,dA,dBha0);

  vmdAsin(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdAsin(vec_len,dA,dBep2);

  vmdAsin(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdAsin(vec_len,dA,dBla2);

  vmdAsin(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdAsin(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdAsin and vmdAsin in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdAsin and vmdAsin in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdAsin and vmdAsin in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdAsin test/example program\n\n");
  printf("           Argument                     vdAsin\n");
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
