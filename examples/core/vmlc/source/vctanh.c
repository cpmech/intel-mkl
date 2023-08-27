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
!    vcTanh  Example Program Text
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

  cA[0].real=-10.0000;cA[0].imag=10.0000;
  cA[1].real=-7.7777;cA[1].imag=7.7777;
  cA[2].real=-5.5555;cA[2].imag=5.5555;
  cA[3].real=-3.3333;cA[3].imag=3.3333;
  cA[4].real=-1.1111;cA[4].imag=1.1111;
  cA[5].real=1.1111;cA[5].imag=-1.1111;
  cA[6].real=3.3333;cA[6].imag=-3.3333;
  cA[7].real=5.5555;cA[7].imag=-5.5555;
  cA[8].real=7.7777;cA[8].imag=-7.7777;
  cA[9].real=10.0000;cA[9].imag=-10.0000;
  cB[0].real=-9.9999999831776032e-001;cB[0].imag=3.7634406702125034e-009;
  cB[1].real=-1.0000003470018366e+000;cB[1].imag=5.3354334283994831e-008;
  cB[2].real=-9.9999655668423026e-001;cB[2].imag=-2.9694976547034457e-005;
  cB[3].real=-9.9764171214624420e-001;cB[3].imag=9.4997702399268746e-004;
  cB[4].real=-1.1225926148824508e+000;cB[4].imag=1.9578899443149567e-001;
  cB[5].real=1.1225926148824508e+000;cB[5].imag=-1.9578899443149567e-001;
  cB[6].real=9.9764171214624420e-001;cB[6].imag=-9.4997702399268746e-004;
  cB[7].real=9.9999655668423026e-001;cB[7].imag=2.9694976547034457e-005;
  cB[8].real=1.0000003470018366e+000;cB[8].imag=-5.3354334283994831e-008;
  cB[9].real=9.9999999831776032e-001;cB[9].imag=-3.7634406702125034e-009;

  vcTanh(vec_len,cA,cBha0);

  vmcTanh(vec_len,cA,cBep1,VML_EP);

  vmlSetMode(VML_EP);
  vcTanh(vec_len,cA,cBep2);

  vmcTanh(vec_len,cA,cBla1,VML_LA);

  vmlSetMode(VML_LA);
  vcTanh(vec_len,cA,cBla2);

  vmcTanh(vec_len,cA,cBha1,VML_HA);

  vmlSetMode(VML_HA);
  vcTanh(vec_len,cA,cBha2);

  for(i=0;i<10;i++) {
    if(cBha0[i].real!=cBha1[i].real || cBha0[i].imag!=cBha1[i].imag || cBha1[i].real!=cBha2[i].real || cBha1[i].imag!=cBha2[i].imag) {
      printf("Error! Difference between vcTanh and vmcTanh in VML_HA mode detected.\n");
      return 1;
    }

    if(cBla1[i].real!=cBla2[i].real || cBla1[i].imag!=cBla2[i].imag) {
      printf("Error! Difference between vcTanh and vmcTanh in VML_LA mode detected.\n");
      return 1;
    }

    if(cBep1[i].real!=cBep2[i].real || cBep1[i].imag!=cBep2[i].imag) {
      printf("Error! Difference between vcTanh and vmcTanh in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vcTanh test/example program\n\n");
  printf("           Argument                           vcTanh\n");
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
