#include <stdlib.h>
#include "scatter.h"

void scatter(float* w,float* x,int C,int W,float*output){
	float* tmp2 = (float*) aligned_alloc(4,(W) * sizeof (float));
	for (int H5 = 0; H5 < W; H5++) {
		for (int H7 = 0; H7 < W; H7++) {
			if (0 <= H5 - (H7)) {
				float tmp3 = 0;
				tmp3 = x[H5];
				float tmp4 = 0;
				tmp4 = w[H5 - (H7)];
				tmp2[H7] = tmp3 * tmp4;
			}
		}
		for (int tmp5 = 0; tmp5 < W; tmp5++) {
			output[tmp5] = output[tmp5] + tmp2[tmp5];
		}
	}
	free(tmp2);
}

