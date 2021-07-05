#include <stdlib.h>
#include "im2collifted.h"

void 
im2collifted(float *x, float *w, int RR, int W, int K, int B, int A, float *output)
{
  float          *tmp2 = (float *)calloc(1, (W) * (RR) * sizeof(float));
  for (int H10 = 0; H10 < W; H10++) {
    for (int H11 = 0; H11 < RR; H11++) {
      if (H10 + H11 < K) {
        tmp2[(RR) * (H10) + H11] = x[H10 + H11];
      }
    }
  }
  float          *x1 = tmp2;
  for (int H13 = 0; H13 < K; H13++) {
    for (int H14 = 0; H14 < W; H14++) {
      for (int H15 = 0; H15 < RR; H15++) {
        float           tmp3 = 0;
        float           tmp4 = 0;
        tmp4 = w[(((B)) * (H13)) + H15];
        float           tmp5 = 0;
        tmp5 = x1[(((RR)) * (H14)) + H15];
        tmp3 = tmp4 * tmp5;
        output[(W) * (H13) + H14] = output[(W) * (H13) + H14] + tmp3;
      }
    }
  }
  free(tmp2);
}
