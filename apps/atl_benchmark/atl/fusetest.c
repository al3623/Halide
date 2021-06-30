#include <stdlib.h>
#include "fusetest.h"

void 
fusetest(int m, int n, float *v, float *output)
{
  for (int H4 = 0; H4 < n; H4++) {
    for (int H5 = 0; H5 < m; H5++) {
      output[(m) * (H4) + H5] = v[(((m)) * (H4)) + H5];
    }
  }
  for (int H9 = 0; H9 < n; H9++) {
    for (int H11 = 0; H11 < 1; H11++) {
      output[(((1 + (m - 1)))) * (H9) + H11 + (n) * (m)] = 1;
    }
    for (int H13 = 0; H13 < (m - 1); H13++) {
      output[(((1 + (m - 1)))) * (H9) + H13 + (n) * (m) + (1)] = v[(((m)) * (H9)) + H13];
    }
  }
}
