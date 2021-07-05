#include <stdlib.h>
#include "concattest0.h"

void 
concattest0(float *l, int m, int n, float *output)
{
  for (int H10 = 0; H10 < 1; H10++) {
    for (int H11 = 0; H11 < n; H11++) {
      output[((1 + (m - (1)))) * (H11) + H10] = l[(((m)) * (H11)) + H10];
    }
  }
  for (int H12 = 1; H12 < m; H12++) {
    for (int H13 = 0; H13 < n; H13++) {
      output[((1 + (m - (1)))) * (H13) + ((H12 - (1)) + 1)] = l[(((m)) * (H13)) + H12];
    }
  }
}
