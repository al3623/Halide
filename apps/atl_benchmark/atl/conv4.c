#include <stdlib.h>
#include "conv4.h"

void 
conv4(int m, int n, float *c, float *output)
{
  for (int H3 = 0; H3 < n; H3++) {
    if (0 <= H3 - (2) && H3 - (2) < m) {
      output[H3] = c[H3 - (2)];
    }
  }
}
