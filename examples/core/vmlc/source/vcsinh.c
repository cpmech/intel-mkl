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
!    vcSinh  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  MKL_Complex8 cA[10],cB[10];
  MKL_Complex8 cBha0[10],cBha1[10],cBha2[10];
  MKL_Complex8           cBla1[10],cBla2[10];
  MKL_Complex8           cBep1[10],cBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  cA[0].real=-7.0000;cA[0].imag=7.0000;
  cA[1].real=-5.4444;cA[1].imag=5.4444;
  cA[2].real=-3.8888;cA[2].imag=3.8888;
  cA[3].real=-2.3333;cA[3].imag=2.3333;
  cA[4].real=-0.7777;cA[4].imag=0.7777;
  cA[5].real=0.7777;cA[5].imag=-0.7777;
  cA[6].real=2.3333;cA[6].imag=-2.3333;
  cA[7].real=3.8888;cA[7].imag=-3.8888;
  cA[8].real=5.4444;cA[8].imag=-5.4444;
  cA[9].real=7.0000;cA[9].imag=-7.0000;
  cB[0].real=-4.1337676142848187e+002;cB[0].imag=3.6023693847656250e+002;
  cB[1].real=-7.7348077021812614e+001;cB[1].imag=-8.6084655761718750e+001;
  cB[2].real=1.7911234921738540e+001;cB[2].imag=-1.6606765747070312e+001;
  cB[3].real=3.5279040476135251e+000;cB[3].imag=3.7633805274963379e+000;
  cB[4].real=-6.1170599407335302e-001;cB[4].imag=9.2473745346069336e-001;
  cB[5].real=6.1170599407335302e-001;cB[5].imag=-9.2473745346069336e-001;
  cB[6].real=-3.5279040476135251e+000;cB[6].imag=-3.7633805274963379e+000;
  cB[7].real=-1.7911234921738540e+001;cB[7].imag=1.6606765747070312e+001;
  cB[8].real=7.7348077021812614e+001;cB[8].imag=8.6084655761718750e+001;
  cB[9].real=4.1337676142848187e+002;cB[9].imag=-3.6023693847656250e+002;

  vcSinh(vec_len,cA,cBha0);

  vmcSinh(vec_len,cA,cBep1,VML_EP);

  vmlSetMode(VML_EP);
  vcSinh(vec_len,cA,cBep2);

  vmcSinh(vec_len,cA,cBla1,VML_LA);

  vmlSetMode(VML_LA);
  vcSinh(vec_len,cA,cBla2);

  vmcSinh(vec_len,cA,cBha1,VML_HA);

  vmlSetMode(VML_HA);
  vcSinh(vec_len,cA,cBha2);

  for(i=0;i<10;i++) {
    if(cBha0[i].real!=cBha1[i].real || cBha0[i].imag!=cBha1[i].imag || cBha1[i].real!=cBha2[i].real || cBha1[i].imag!=cBha2[i].imag) {
      printf("Error! Difference between vcSinh and vmcSinh in VML_HA mode detected.\n");
      return 1;
    }

    if(cBla1[i].real!=cBla2[i].real || cBla1[i].imag!=cBla2[i].imag) {
      printf("Error! Difference between vcSinh and vmcSinh in VML_LA mode detected.\n");
      return 1;
    }

    if(cBep1[i].real!=cBep2[i].real || cBep1[i].imag!=cBep2[i].imag) {
      printf("Error! Difference between vcSinh and vmcSinh in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vcSinh test/example program\n\n");
  printf("           Argument                           vcSinh\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("   % .4f %+.4f*i      % .10f %+.10f*i\n",cA[i].real,cA[i].imag,cBha0[i].real,cBha0[i].imag);
    CurRMS=crelerr(cB[i],cBha0[i]);
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
