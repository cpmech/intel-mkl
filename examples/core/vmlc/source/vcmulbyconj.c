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
!    vcMulByConj  Example Program Text
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

  cA[0].real=-100.0000;cA[0].imag=100.0000;
  cA[1].real=-77.7777;cA[1].imag=77.7777;
  cA[2].real=-55.5555;cA[2].imag=55.5555;
  cA[3].real=-33.3333;cA[3].imag=33.3333;
  cA[4].real=-11.1111;cA[4].imag=11.1111;
  cA[5].real=11.1111;cA[5].imag=-11.1111;
  cA[6].real=33.3333;cA[6].imag=-33.3333;
  cA[7].real=55.5555;cA[7].imag=-55.5555;
  cA[8].real=77.7777;cA[8].imag=-77.7777;
  cA[9].real=100.0000;cA[9].imag=-100.0000;
  cB[0].real=2.0000000000000000e+004;cB[0].imag=0.0000000000000000e+000;
  cB[1].real=1.2098741959948209e+004;cB[1].imag=0.0000000000000000e+000;
  cB[2].real=6.1728271672816772e+003;cB[2].imag=0.0000000000000000e+000;
  cB[3].real=2.2222179836717260e+003;cB[3].imag=0.0000000000000000e+000;
  cB[4].real=2.4691309516836372e+002;cB[4].imag=0.0000000000000000e+000;
  cB[5].real=2.4691309516836372e+002;cB[5].imag=0.0000000000000000e+000;
  cB[6].real=2.2222179836717260e+003;cB[6].imag=0.0000000000000000e+000;
  cB[7].real=6.1728271672816772e+003;cB[7].imag=0.0000000000000000e+000;
  cB[8].real=1.2098741959948209e+004;cB[8].imag=0.0000000000000000e+000;
  cB[9].real=2.0000000000000000e+004;cB[9].imag=0.0000000000000000e+000;

  vcMulByConj(vec_len,cA,cA,cBha0);

  vmcMulByConj(vec_len,cA,cA,cBep1,VML_EP);

  vmlSetMode(VML_EP);
  vcMulByConj(vec_len,cA,cA,cBep2);

  vmcMulByConj(vec_len,cA,cA,cBla1,VML_LA);

  vmlSetMode(VML_LA);
  vcMulByConj(vec_len,cA,cA,cBla2);

  vmcMulByConj(vec_len,cA,cA,cBha1,VML_HA);

  vmlSetMode(VML_HA);
  vcMulByConj(vec_len,cA,cA,cBha2);

  for(i=0;i<10;i++) {
    if(cBha0[i].real!=cBha1[i].real || cBha0[i].imag!=cBha1[i].imag || cBha1[i].real!=cBha2[i].real || cBha1[i].imag!=cBha2[i].imag) {
      printf("Error! Difference between vcMulByConj and vmcMulByConj in VML_HA mode detected.\n");
      return 1;
    }

    if(cBla1[i].real!=cBla2[i].real || cBla1[i].imag!=cBla2[i].imag) {
      printf("Error! Difference between vcMulByConj and vmcMulByConj in VML_LA mode detected.\n");
      return 1;
    }

    if(cBep1[i].real!=cBep2[i].real || cBep1[i].imag!=cBep2[i].imag) {
      printf("Error! Difference between vcMulByConj and vmcMulByConj in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vcMulByConj test/example program\n\n");
  printf("           Arguments                           vcMulByConj\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("   % .2f %+.2f*i   % .2f %+.2f*i      % .2f %+.2f*i\n",cA[i].real,cA[i].imag,cA[i].real,cA[i].imag,cBha0[i].real,cBha0[i].imag);
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
