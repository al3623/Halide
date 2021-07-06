#include <stdlib.h>
#include "gather.h"

void gather(float* w,float* x,int C,int W,float*output){
#pragma omp parallel for
	for (int H6 = 0; H6 < W; H6++) {
		for (int H7 = 0; H7 < C; H7++) {
			float tmp2 = 0;
			if (H6 + H7 < W) {
				float tmp3 = 0;
				tmp3 = x[H6 + H7];
				float tmp4 = 0;
				tmp4 = w[H7];
				tmp2 = tmp3 * tmp4;
			}
			output[H6] = output[H6] + tmp2;
		}
	}
}

