#include <stdlib.h>
#include "blurtwo.h"

void 
blurtwo(float *v, int M, int N, float *output)
{
  float          *tmp2 = (float *)calloc(1, ((N + 1 + 1 + 0)) * (M) * sizeof(float));
  for (int H7 = 0; H7 < (N + 1 + 1 + 0); H7++) {
    for (int H8 = 0; H8 < M; H8++) {
      if (0 <= H7 - (1) && H7 - (1) < N) {
        float           tmp3 = 0;
        float           tmp4 = 0;
        if (0 <= H8 - (1)) {
          tmp4 = v[(((M)) * (H7 - (1))) + H8 - (1)];
        }
        float           tmp5 = 0;
        tmp5 = v[(((M)) * (H7 - (1))) + H8];
        tmp3 = tmp4 + tmp5;
        float           tmp6 = 0;
        if (H8 + 1 < M) {
          tmp6 = v[(((M)) * (H7 - (1))) + H8 + 1];
        }
        tmp2[(M) * (H7) + H8] = tmp3 + tmp6;
      }
    }
  }
  float          *x0 = tmp2;
  for (int H10 = 0; H10 < N; H10++) {
    for (int H11 = 0; H11 < M; H11++) {
      float           tmp7 = 0;
      float           tmp8 = 0;
      tmp8 = x0[(((M)) * (H10)) + H11];
      float           tmp9 = 0;
      tmp9 = x0[(((M)) * (H10 + 1)) + H11];
      tmp7 = tmp8 + tmp9;
      float           tmp10 = 0;
      tmp10 = x0[(((M)) * (H10 + 2)) + H11];
      output[(M) * (H10) + H11] = tmp7 + tmp10;
    }
  }
  free(tmp2);
}
