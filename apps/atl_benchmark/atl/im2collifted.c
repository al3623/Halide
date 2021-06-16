#include <stdlib.h>
#include "im2collifted.h"

void im2collifted(u_int8_t* x,u_int8_t* w,int RR,int W,int K,int B,int A,u_int8_t*output){
	u_int8_t* tmp2 = (u_int8_t*) calloc(1,(W) * (RR) * sizeof (u_int8_t));
	for (int H6 = 0; H6 < W; H6++) {
		for (int H7 = 0; H7 < RR; H7++) {
			if (H6 + H7 < K) {
				tmp2[(RR) * (H6) + H7] = x[H6 + H7];
			}
		}
	}
	u_int8_t* x0 = tmp2;
	for (int H10 = 0; H10 < K; H10++) {
		for (int H11 = 0; H11 < W; H11++) {
			for (int H12 = 0; H12 < RR; H12++) {
				u_int8_t tmp3 = 0;
				u_int8_t tmp4 = 0;
				tmp4 = w[(((B)) * (H10)) + H12];
				u_int8_t tmp5 = 0;
				tmp5 = x0[(((RR)) * (H11)) + H12];
				tmp3 = tmp4 * tmp5;
				output[(W) * (H10) + H11] = output[(W) * (H10) + H11] + tmp3;
			}
		}
	}
	free(tmp2);
}

