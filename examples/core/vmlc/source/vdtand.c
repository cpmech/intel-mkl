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
!     vdTand Example Program Text
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
  dB[0]=-3.0785224908226788e-01;
  dB[1]=-2.3495669815647119e-01;
  dB[2]=-1.6435311698545926e-01;
  dB[3]=-9.5309739161450885e-02;
  dB[4]=-2.7155268405913695e-02;
  dB[5]=4.4631488524599937e-02;
  dB[6]=1.1295271648547688e-01;
  dB[7]=1.8233125277748685e-01;
  dB[8]=2.5345121325212433e-01;
  dB[9]=3.2706482332959891e-01;

  vdTand(vec_len,dA,dBha0);

  vmdTand(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdTand(vec_len,dA,dBep2);

  vmdTand(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdTand(vec_len,dA,dBla2);

  vmdTand(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdTand(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdTand and vmdTand in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdTand and vmdTand in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdTand and vmdTand in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdTand test/example program\n\n");
  printf("           Argument                     vdTand\n");
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
