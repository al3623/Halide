#include <stdlib.h>
#include "blurim.h"

void 
blurim(float *v, int M, int N, float *output)
{
  for (int H3 = 0; H3 < N; H3++) {
    for (int H4 = 0; H4 < M; H4++) {
      float           tmp2 = 0;
      float           tmp3 = 0;
      if (0 <= H3 - (1) && H3 - (1) < N) {
        float           tmp4 = 0;
        float           tmp5 = 0;
        if (0 <= H4 - (1)) {
          tmp5 = v[(((M)) * (H3 - (1))) + H4 - (1)];
        }
        float           tmp6 = 0;
        tmp6 = v[(((M)) * (H3 - (1))) + H4];
        tmp4 = tmp5 + tmp6;
        float           tmp7 = 0;
        if (H4 + 1 < M) {
          tmp7 = v[(((M)) * (H3 - (1))) + H4 + 1];
        }
        tmp3 = tmp4 + tmp7;
      }
      float           tmp8 = 0;
      if (0 <= H3) {
        float           tmp9 = 0;
        float           tmp10 = 0;
        if (0 <= H4 - (1)) {
          tmp10 = v[(((M)) * (H3)) + H4 - (1)];
        }
        float           tmp11 = 0;
        tmp11 = v[(((M)) * (H3)) + H4];
        tmp9 = tmp10 + tmp11;
        float           tmp12 = 0;
        if (H4 + 1 < M) {
          tmp12 = v[(((M)) * (H3)) + H4 + 1];
        }
        tmp8 = tmp9 + tmp12;
      }
      tmp2 = tmp3 + tmp8;
      float           tmp13 = 0;
      if (0 <= H3 + 1 && H3 + 1 < N) {
        float           tmp14 = 0;
        float           tmp15 = 0;
        if (0 <= H4 - (1)) {
          tmp15 = v[(((M)) * (H3 + 1)) + H4 - (1)];
        }
        float           tmp16 = 0;
        tmp16 = v[(((M)) * (H3 + 1)) + H4];
        tmp14 = tmp15 + tmp16;
        float           tmp17 = 0;
        if (H4 + 1 < M) {
          tmp17 = v[(((M)) * (H3 + 1)) + H4 + 1];
        }
        tmp13 = tmp14 + tmp17;
      }
      output[(M) * (H3) + H4] = tmp2 + tmp13;
    }
  }
}
