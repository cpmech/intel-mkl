/*******************************************************************************
* Copyright 2001-2020 Intel Corporation.
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
!    vsAsin  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

#define INCA 3
#define INCB 5

int main()
{
  float fA[10],fB[10];
  float fBha0[10],fBha1[10],fBha2[10];
  float           fBla1[10],fBla2[10];
  float           fBep1[10],fBep2[10];
  float CurRMS,MaxRMS=0.0;

  float fA_I[10*INCA],fB_I[10*INCB];
  float fBha0_I[10*INCB],fBha1_I[10*INCB],fBha2_I[10*INCB];
  float                  fBla1_I[10*INCB],fBla2_I[10*INCB];
  float                  fBep1_I[10*INCB],fBep2_I[10*INCB];
  float CurRMS_I,MaxRMS_I=0.0;
  MKL_INT inca=INCA,incb=INCB;

  MKL_INT i=0,vec_len=10;

  fA[0]=-1.0000;
  fA[1]=-0.7777;
  fA[2]=-0.5555;
  fA[3]=-0.3333;
  fA[4]=-0.1111;
  fA[5]=0.1111;
  fA[6]=0.3333;
  fA[7]=0.5555;
  fA[8]=0.7777;
  fA[9]=1.0000;
  fB[0]=-1.5707963267948966e+000;
  fB[1]=-8.9099878474680128e-001;
  fB[2]=-5.8896412141634957e-001;
  fB[3]=-3.3980154846925537e-001;
  fB[4]=-1.1132983715080322e-001;
  fB[5]=1.1132983715080322e-001;
  fB[6]=3.3980154846925537e-001;
  fB[7]=5.8896412141634957e-001;
  fB[8]=8.9099878474680128e-001;
  fB[9]=1.5707963267948966e+000;

  for(i=0;i<10;i++) {
    fA_I[i*inca]=fA[i];
    fB_I[i*incb]=fB[i];
  }

  vsAsin(vec_len,fA,fBha0);
  vsAsinI(vec_len,fA_I,inca,fBha0_I,incb);

  vmsAsin(vec_len,fA,fBep1,VML_EP);
  vmsAsinI(vec_len,fA_I,inca,fBep1_I,incb,VML_EP);

  vmlSetMode(VML_EP);
  vsAsin(vec_len,fA,fBep2);
  vsAsinI(vec_len,fA_I,inca,fBep2_I,incb);

  vmsAsin(vec_len,fA,fBla1,VML_LA);
  vmsAsinI(vec_len,fA_I,inca,fBla1_I,incb,VML_LA);

  vmlSetMode(VML_LA);
  vsAsin(vec_len,fA,fBla2);
  vsAsinI(vec_len,fA_I,inca,fBla2_I,incb);

  vmsAsin(vec_len,fA,fBha1,VML_HA);
  vmsAsinI(vec_len,fA_I,inca,fBha1_I,incb,VML_HA);

  vmlSetMode(VML_HA);
  vsAsin(vec_len,fA,fBha2);
  vsAsinI(vec_len,fA_I,inca,fBha2_I,incb);

  for(i=0;i<10;i++) {
    if(fBha0[i]!=fBha1[i] || fBha1[i]!=fBha2[i]) {
      printf("Error! Difference between vsAsin and vmsAsin in VML_HA mode detected.\n");
      return 1;
    }

    if(fBha0_I[i*incb]!=fBha1_I[i*incb] || fBha1_I[i*incb]!=fBha2_I[i*incb]) {
      printf("Error! Difference between vsAsinI and vmsAsinI in VML_HA mode detected.\n");
      return 1;
    }

    if(fBla1[i]!=fBla2[i]) {
      printf("Error! Difference between vsAsin and vmsAsin in VML_LA mode detected.\n");
      return 1;
    }

    if(fBla1_I[i*incb]!=fBla2_I[i*incb]) {
      printf("Error! Difference between vsAsinI and vmsAsinI in VML_LA mode detected.\n");
      return 1;
    }

    if(fBep1[i]!=fBep2[i]) {
      printf("Error! Difference between vsAsin and vmsAsin in VML_EP mode detected.\n");
      return 1;
    }

    if(fBep1_I[i*incb]!=fBep2_I[i*incb]) {
      printf("Error! Difference between vsAsinI and vmsAsinI in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vsAsin test/example program\n\n");
  printf("           Argument                     vsAsin\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e\n",fA[i],fBha0[i]);
    CurRMS=srelerr(fB[i],fBha0[i]);
    if(CurRMS>MaxRMS) MaxRMS=CurRMS;
  }
  printf("\n");
  printf("vsAsinI test/example program\n\n");
  printf("           Argument                     vsAsin\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("% 25.14f % 25.14e\n",fA_I[i*inca],fBha0_I[i*incb]);
    CurRMS_I=srelerr(fB_I[i*incb],fBha0_I[i*incb]);
    if(CurRMS_I>MaxRMS_I) MaxRMS_I=CurRMS_I;
  }
  printf("\n");
  if(MaxRMS>=1e-5) {
    printf("Error! Relative accuracy is %.16f\n",MaxRMS);
    return 1;
  }
  else {
    printf("Relative accuracy is %.16f\n",MaxRMS);
  }

  printf("\n");

  if(MaxRMS_I>=1e-5) {
    printf("Error! Relative strided accuracy is %.16f\n",MaxRMS_I);
    return 1;
  }
  else {
    printf("Relative strided accuracy is %.16f\n",MaxRMS_I);
  }
  return 0;
}
