#include <stdlib.h>
#include "blurtwo.h"

void blurtwo(u_int8_t* v,int M,int N,u_int8_t*output){
	u_int8_t* tmp2 = (u_int8_t*) calloc(1,(N + 2) * (M) * sizeof (u_int8_t));
	for (int H4 = 0; H4 < N + 2; H4++) {
		for (int H5 = 0; H5 < M; H5++) {
			if (0 <= H4 - (1) && H4 - (1) < N) {
				u_int8_t tmp3 = 0;
				u_int8_t tmp4 = 0;
				if (0 <= H5 - (1)) {
					tmp4 = v[(((M)) * (H4 - (1))) + H5 - (1)];
				}
				u_int8_t tmp5 = 0;
				tmp5 = v[(((M)) * (H4 - (1))) + H5];
				tmp3 = tmp4 + tmp5;
				u_int8_t tmp6 = 0;
				if (H5 + 1 < M) {
					tmp6 = v[(((M)) * (H4 - (1))) + H5 + 1];
				}
				tmp2[(M) * (H4) + H5] = tmp3 + tmp6;
			}
		}
	}
	u_int8_t* x = tmp2;
	for (int H17 = 0; H17 < N; H17++) {
		for (int H18 = 0; H18 < M; H18++) {
			u_int8_t tmp7 = 0;
			u_int8_t tmp8 = 0;
			tmp8 = x[(((M)) * (H17)) + H18];
			u_int8_t tmp9 = 0;
			tmp9 = x[(((M)) * (H17 + 1)) + H18];
			tmp7 = tmp8 + tmp9;
			u_int8_t tmp10 = 0;
			tmp10 = x[(((M)) * (H17 + 2)) + H18];
			output[(M) * (H17) + H18] = tmp7 + tmp10;
		}
	}
	free(tmp2);
}

