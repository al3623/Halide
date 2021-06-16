#include <stdlib.h>
#include "blurim.h"

void blurim(u_int8_t* v,int M,int N,u_int8_t*output){
	for (int H3 = 0; H3 < N; H3++) {
		for (int H4 = 0; H4 < M; H4++) {
			u_int8_t tmp2 = 0;
			u_int8_t tmp3 = 0;
			if (0 <= H3 - (1)) {
				u_int8_t tmp4 = 0;
				u_int8_t tmp5 = 0;
				if (0 <= H4 - (1)) {
					tmp5 = v[(((M)) * (H3 - (1))) + H4 - (1)];
				}
				u_int8_t tmp6 = 0;
				tmp6 = v[(((M)) * (H3 - (1))) + H4];
				tmp4 = tmp5 + tmp6;
				u_int8_t tmp7 = 0;
				if (H4 + 1 < M) {
					tmp7 = v[(((M)) * (H3 - (1))) + H4 + 1];
				}
				tmp3 = tmp4 + tmp7;
			}
			u_int8_t tmp8 = 0;
			u_int8_t tmp9 = 0;
			u_int8_t tmp10 = 0;
			if (0 <= H4 - (1)) {
				tmp10 = v[(((M)) * (H3)) + H4 - (1)];
			}
			u_int8_t tmp11 = 0;
			tmp11 = v[(((M)) * (H3)) + H4];
			tmp9 = tmp10 + tmp11;
			u_int8_t tmp12 = 0;
			if (H4 + 1 < M) {
				tmp12 = v[(((M)) * (H3)) + H4 + 1];
			}
			tmp8 = tmp9 + tmp12;
			tmp2 = tmp3 + tmp8;
			u_int8_t tmp13 = 0;
			if (H3 + 1 < N) {
				u_int8_t tmp14 = 0;
				u_int8_t tmp15 = 0;
				if (0 <= H4 - (1)) {
					tmp15 = v[(((M)) * (H3 + 1)) + H4 - (1)];
				}
				u_int8_t tmp16 = 0;
				tmp16 = v[(((M)) * (H3 + 1)) + H4];
				tmp14 = tmp15 + tmp16;
				u_int8_t tmp17 = 0;
				if (H4 + 1 < M) {
					tmp17 = v[(((M)) * (H3 + 1)) + H4 + 1];
				}
				tmp13 = tmp14 + tmp17;
			}
			output[(M) * (H3) + H4] = tmp2 + tmp13;
		}
	}
}

