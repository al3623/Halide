#include <stdlib.h>
#include "scatter.h"

void scatter(u_int8_t* w,u_int8_t* x,int C,int W,u_int8_t*output){
	u_int8_t* tmp2 = (u_int8_t*) aligned_alloc(4,(W) * sizeof (u_int8_t));
	for (int H5 = 0; H5 < W; H5++) {
		for (int H7 = 0; H7 < W; H7++) {
			if (0 <= H5 - (H7)) {
				u_int8_t tmp3 = 0;
				tmp3 = x[H5];
				u_int8_t tmp4 = 0;
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

