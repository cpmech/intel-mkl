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
!    vzAbs  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  MKL_Complex16 zA[10];
  double dB[10];
  double dBha0[10],dBha1[10],dBha2[10];
  double           dBla1[10],dBla2[10];
  double           dBep1[10],dBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  zA[0].real=-1000.0000;zA[0].imag=1000.0000;
  zA[1].real=-777.7777;zA[1].imag=777.7777;
  zA[2].real=-555.5555;zA[2].imag=555.5555;
  zA[3].real=-333.3333;zA[3].imag=333.3333;
  zA[4].real=-111.1111;zA[4].imag=111.1111;
  zA[5].real=111.1111;zA[5].imag=-111.1111;
  zA[6].real=333.3333;zA[6].imag=-333.3333;
  zA[7].real=555.5555;zA[7].imag=-555.5555;
  zA[8].real=777.7777;zA[8].imag=-777.7777;
  zA[9].real=1000.0000;zA[9].imag=-1000.0000;
  dB[0]=1.4142135623730951e+003;
  dB[1]=1.0999437718513525e+003;
  dB[2]=7.8567412275096603e+002;
  dB[3]=4.7140447365057963e+002;
  dB[4]=1.5713482455019320e+002;
  dB[5]=1.5713482455019320e+002;
  dB[6]=4.7140447365057963e+002;
  dB[7]=7.8567412275096603e+002;
  dB[8]=1.0999437718513525e+003;
  dB[9]=1.4142135623730951e+003;

  vzAbs(vec_len,zA,dBha0);

  vmzAbs(vec_len,zA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vzAbs(vec_len,zA,dBep2);

  vmzAbs(vec_len,zA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vzAbs(vec_len,zA,dBla2);

  vmzAbs(vec_len,zA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vzAbs(vec_len,zA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vzAbs and vmzAbs in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vzAbs and vmzAbs in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vzAbs and vmzAbs in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vzAbs test/example program\n\n");
  printf("           Argument                           vzAbs\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("   % .4f %+.4f*i      % .10f\n",zA[i].real,zA[i].imag,dBha0[i]);
    CurRMS=drelerr(dB[i],dBha0[i]);
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
