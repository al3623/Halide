#include <stdlib.h>
#include "conv1.h"

void 
conv1(int m, int n, float *c, float *output)
{
  float          *tmp4 = (float *)aligned_alloc(4, (n - ((-(m)) + 1)) * sizeof(float));
  for (int H3 = 0; H3 < n; H3++) {
    for (int H4 = 0; H4 < m; H4++) {
      float           tmp2 = 0;
      if (0 <= H3 - (H4)) {
        float           tmp3 = 0;
        for (int H9 = (-(m)) + 1; H9 < n; H9++) {
          if (H9 == 2 + (-(m)) + 1) {
            tmp4[(H9 - ((-(m)) + 1))] = 1;
          }
        }
        tmp3 = tmp4[H3 - (H4)];
        float           tmp5 = 0;
        tmp5 = c[H4];
        tmp2 = tmp3 * tmp5;
      }
      output[H3] = output[H3] + tmp2;
    }
  }
  free(tmp4);
}
