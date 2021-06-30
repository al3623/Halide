#include <stdlib.h>
#include "blurtwo.h"

void 
blurtwo(float *v, int M, int N, float *output)
{
  float          *tmp2 = (float *)aligned_alloc(4, ((N + 2)) * (M) * sizeof(float));
  for (int H4 = 0; H4 < (N + 2); H4++) {
    for (int H5 = 0; H5 < M; H5++) {
      if (0 <= H4 - (1) && H4 - (1) < N) {
        float           tmp3 = 0;
        float           tmp4 = 0;
        if (0 <= H5 - (1)) {
          tmp4 = v[(((M)) * (H4 - (1))) + H5 - (1)];
        }
        float           tmp5 = 0;
        tmp5 = v[(((M)) * (H4 - (1))) + H5];
        tmp3 = tmp4 + tmp5;
        float           tmp6 = 0;
        if (H5 + 1 < M) {
          tmp6 = v[(((M)) * (H4 - (1))) + H5 + 1];
        }
        tmp2[(M) * (H4) + H5] = tmp3 + tmp6;
      }
    }
  }
  float          *x = tmp2;
  for (int H17 = 0; H17 < N; H17++) {
    for (int H18 = 0; H18 < M; H18++) {
      float           tmp7 = 0;
      float           tmp8 = 0;
      tmp8 = x[(((M)) * (H17)) + H18];
      float           tmp9 = 0;
      tmp9 = x[(((M)) * (H17 + 1)) + H18];
      tmp7 = tmp8 + tmp9;
      float           tmp10 = 0;
      tmp10 = x[(((M)) * (H17 + 2)) + H18];
      output[(M) * (H17) + H18] = tmp7 + tmp10;
    }
  }
  free(tmp2);
}
