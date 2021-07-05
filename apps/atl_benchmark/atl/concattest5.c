#include <stdlib.h>
#include "concattest5.h"

void 
concattest5(float *v, int m, int n, float *output)
{
  for (int H8 = 0; H8 < ((n) + (64) - 1) / (64); H8++) {
    for (int H9 = 0; H9 < ((m) + (64) - 1) / (64); H9++) {
      for (int H16 = 0; H16 < 1; H16++) {
        for (int H17 = 0; H17 < 64; H17++) {
          if ((H9) * (64) + H17 < m) {
            if ((H8) * (64) + H16 < n) {
              output[(m) * (((1 + (64 - (1)))) * (H8) + H16) + (64) * (H9) + H17] = v[(((m)) * ((H8) * (64) + H16)) + (H9) * (64) + H17];
            }
          }
        }
      }
      for (int H18 = 1; H18 < 64; H18++) {
        for (int H19 = 0; H19 < 64; H19++) {
          if ((H9) * (64) + H19 < m) {
            if ((H8) * (64) + H18 < n) {
              output[(m) * (((1 + (64 - (1)))) * (H8) + ((H18 - (1)) + 1)) + (64) * (H9) + H19] = v[(((m)) * ((H8) * (64) + H18)) + (H9) * (64) + H19];
            }
          }
        }
      }
    }
  }
}
