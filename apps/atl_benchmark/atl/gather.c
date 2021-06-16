#include <stdlib.h>
#include "gather.h"

void gather(u_int8_t* w,u_int8_t* x,int C,int W,u_int8_t*output){
	for (int H5 = 0; H5 < W; H5++) {
		for (int H6 = 0; H6 < C; H6++) {
			u_int8_t tmp2 = 0;
			if (H5 + H6 < W) {
				u_int8_t tmp3 = 0;
				tmp3 = x[H5 + H6];
				u_int8_t tmp4 = 0;
				tmp4 = w[H6];
				tmp2 = tmp3 * tmp4;
			}
			output[H5] = output[H5] + tmp2;
		}
	}
}

