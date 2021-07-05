#include <stdlib.h>
#include "concattest2.h"

void 
concattest2(float *v, int m, int n, float *output)
{
  for (int H15 = 0; H15 < 1; H15++) {
    for (int H19 = 0; H19 < 1; H19++) {
      output[((1 + (m - (1)))) * (H19) + H15] = v[(((m)) * (H19)) + H15];
    }
    for (int H20 = 1; H20 < n; H20++) {
      output[((1 + (m - (1)))) * (((H20 - (1)) + 1)) + H15] = v[(((m)) * (H20)) + H15];
    }
  }
  for (int H21 = 1; H21 < m; H21++) {
    for (int H22 = 0; H22 < n; H22++) {
      output[((1 + (m - (1)))) * (H22) + ((H21 - (1)) + 1)] = v[(((m)) * (H22)) + H21];
    }
  }
}
