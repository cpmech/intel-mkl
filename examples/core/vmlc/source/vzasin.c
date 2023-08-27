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
!    vzAsin  Example Program Text
!******************************************************************************/

#include <stdio.h>
#include "mkl_vml.h"

#include "_rms.h"

int main()
{
  MKL_Complex16 zA[10],zB[10];
  MKL_Complex16 zBha0[10],zBha1[10],zBha2[10];
  MKL_Complex16           zBla1[10],zBla2[10];
  MKL_Complex16           zBep1[10],zBep2[10];
  float CurRMS,MaxRMS=0.0;

  MKL_INT i=0,vec_len=10;

  zA[0].real=-1.0000;zA[0].imag=1.0000;
  zA[1].real=-0.7777;zA[1].imag=0.7777;
  zA[2].real=-0.5555;zA[2].imag=0.5555;
  zA[3].real=-0.3333;zA[3].imag=0.3333;
  zA[4].real=-0.1111;zA[4].imag=0.1111;
  zA[5].real=0.1111;zA[5].imag=-0.1111;
  zA[6].real=0.3333;zA[6].imag=-0.3333;
  zA[7].real=0.5555;zA[7].imag=-0.5555;
  zA[8].real=0.7777;zA[8].imag=-0.7777;
  zA[9].real=1.0000;zA[9].imag=-1.0000;
  zB[0].real=-6.6623943249251527e-001;zB[0].imag=1.0612750619050357e+000;
  zB[1].real=-6.0135587708509519e-001;zB[1].imag=8.4060455895425301e-001;
  zB[2].real=-4.8944080432477105e-001;zB[2].imag=5.9386557353258917e-001;
  zB[3].real=-3.1990734647712815e-001;zB[3].imag=3.4427275439844690e-001;
  zB[4].real=-1.1063788765091863e-001;zB[4].imag=1.1155195888225219e-001;
  zB[5].real=1.1063788765091863e-001;zB[5].imag=-1.1155195888225219e-001;
  zB[6].real=3.1990734647712815e-001;zB[6].imag=-3.4427275439844690e-001;
  zB[7].real=4.8944080432477105e-001;zB[7].imag=-5.9386557353258917e-001;
  zB[8].real=6.0135587708509519e-001;zB[8].imag=-8.4060455895425301e-001;
  zB[9].real=6.6623943249251527e-001;zB[9].imag=-1.0612750619050357e+000;

  vzAsin(vec_len,zA,zBha0);

  vmzAsin(vec_len,zA,zBep1,VML_EP);

  vmlSetMode(VML_EP);
  vzAsin(vec_len,zA,zBep2);

  vmzAsin(vec_len,zA,zBla1,VML_LA);

  vmlSetMode(VML_LA);
  vzAsin(vec_len,zA,zBla2);

  vmzAsin(vec_len,zA,zBha1,VML_HA);

  vmlSetMode(VML_HA);
  vzAsin(vec_len,zA,zBha2);

  for(i=0;i<10;i++) {
    if(zBha0[i].real!=zBha1[i].real || zBha0[i].imag!=zBha1[i].imag || zBha1[i].real!=zBha2[i].real || zBha1[i].imag!=zBha2[i].imag) {
      printf("Error! Difference between vzAsin and vmzAsin in VML_HA mode detected.\n");
      return 1;
    }

    if(zBla1[i].real!=zBla2[i].real || zBla1[i].imag!=zBla2[i].imag) {
      printf("Error! Difference between vzAsin and vmzAsin in VML_LA mode detected.\n");
      return 1;
    }

    if(zBep1[i].real!=zBep2[i].real || zBep1[i].imag!=zBep2[i].imag) {
      printf("Error! Difference between vzAsin and vmzAsin in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vzAsin test/example program\n\n");
  printf("           Argument                           vzAsin\n");
  printf("===============================================================================\n");
  for(i=0;i<10;i++) {
    printf("   % .4f %+.4f*i      % .10f %+.10f*i\n",zA[i].real,zA[i].imag,zBha0[i].real,zBha0[i].imag);
    CurRMS=zrelerr(zB[i],zBha0[i]);
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
