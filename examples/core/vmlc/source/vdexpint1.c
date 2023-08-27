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
!    vdExpInt1  Example Program Text
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

  dA[0]=0.0099;
  dA[1]=1.1188;
  dA[2]=2.2277;
  dA[3]=3.3366;
  dA[4]=4.4455;
  dA[5]=5.5544;
  dA[6]=6.6633;
  dA[7]=7.7722;
  dA[8]=8.8811;
  dA[9]=10.9900;
  dB[0]=4.0478804082456561e+000;
  dB[1]=1.8040245017300815e-001;
  dB[2]=3.5823720500837803e-002;
  dB[3]=8.5395678123381378e-003;
  dB[4]=2.2125287051014398e-003;
  dB[5]=6.0177551568345372e-004;
  dB[6]=1.6900054855506348e-004;
  dB[7]=4.8555136832843647e-005;
  dB[8]=1.4190386714418714e-005;
  dB[9]=1.4155667910435293e-006;

  vdExpInt1(vec_len,dA,dBha0);

  vmdExpInt1(vec_len,dA,dBep1,VML_EP);

  vmlSetMode(VML_EP);
  vdExpInt1(vec_len,dA,dBep2);

  vmdExpInt1(vec_len,dA,dBla1,VML_LA);

  vmlSetMode(VML_LA);
  vdExpInt1(vec_len,dA,dBla2);

  vmdExpInt1(vec_len,dA,dBha1,VML_HA);

  vmlSetMode(VML_HA);
  vdExpInt1(vec_len,dA,dBha2);

  for(i=0;i<10;i++) {
    if(dBha0[i]!=dBha1[i] || dBha1[i]!=dBha2[i]) {
      printf("Error! Difference between vdExpInt1 and vmdExpInt1 in VML_HA mode detected.\n");
      return 1;
    }

    if(dBla1[i]!=dBla2[i]) {
      printf("Error! Difference between vdExpInt1 and vmdExpInt1 in VML_LA mode detected.\n");
      return 1;
    }

    if(dBep1[i]!=dBep2[i]) {
      printf("Error! Difference between vdExpInt1 and vmdExpInt1 in VML_EP mode detected.\n");
      return 1;
    }
  }

  printf("vdExpInt1 test/example program\n\n");
  printf("           Argument                     vdExpInt1\n");
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
