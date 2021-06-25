#include <stdlib.h>
#include "gather.h"

void gather(float* w,float* x,int C,int W,float*output){
	for (int H5 = 0; H5 < W; H5++) {
		for (int H6 = 0; H6 < C; H6++) {
			float tmp2 = 0;
			if (H5 + H6 < W) {
				float tmp3 = 0;
				tmp3 = x[H5 + H6];
				float tmp4 = 0;
				tmp4 = w[H6];
				tmp2 = tmp3 * tmp4;
			}
			output[H5] = output[H5] + tmp2;
		}
	}
}

