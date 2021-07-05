#include <stdlib.h>
#include "scatter.h"

void 
scatter(float *w, float *x, int C, int W, float *output)
{
  float          *tmp2 = (float *)calloc(1, (W) * sizeof(float));
  for (int H6 = 0; H6 < W; H6++) {
    for (int H8 = 0; H8 < W; H8++) {
      if (0 <= H6 - (H8)) {
        float           tmp3 = 0;
        tmp3 = x[H6];
        float           tmp4 = 0;
        tmp4 = w[H6 - (H8)];
        tmp2[H8] = tmp3 * tmp4;
      }
    }
    for (int tmp5 = 0; tmp5 < W; tmp5++) {
      output[tmp5] = output[tmp5] + tmp2[tmp5];
    }
  }
  free(tmp2);
}
