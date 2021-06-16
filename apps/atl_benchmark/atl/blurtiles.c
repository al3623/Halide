#include <stdlib.h>
#include "blurtiles.h"

void blurtiles(u_int8_t* v,int M,int N,u_int8_t*output){
	u_int8_t* tmp2 = (u_int8_t*) calloc(1,(6) * (4) * sizeof (u_int8_t));
	for (int H3 = 0; H3 < ((N) + (4) - 1 ) / (4); H3++) {
		for (int H4 = 0; H4 < ((M) + (4) - 1 ) / (4); H4++) {
			for (int H6 = 0; H6 < 6; H6++) {
				for (int H7 = 0; H7 < 4; H7++) {
					if ((H4) * (4) + H7 < M) {
						if (0 <= (H3) * (4) + H6 - (1) && (H3) * (4) + H6 - (1) < N) {
							u_int8_t tmp3 = 0;
							u_int8_t tmp4 = 0;
							if (0 <= (H4) * (4) + H7 - (1)) {
								tmp4 = v[(((M)) * ((H3) * (4) + H6 - (1))) + (H4) * (4) + H7 - (1)];
							}
							u_int8_t tmp5 = 0;
							tmp5 = v[(((M)) * ((H3) * (4) + H6 - (1))) + (H4) * (4) + H7];
							tmp3 = tmp4 + tmp5;
							u_int8_t tmp6 = 0;
							if ((H4) * (4) + H7 + 1 < M) {
								tmp6 = v[(((M)) * ((H3) * (4) + H6 - (1))) + (H4) * (4) + H7 + 1];
							}
							tmp2[(4) * (H6) + H7] = tmp3 + tmp6;
						}
					}
				}
			}
			u_int8_t* x = tmp2;
			for (int H19 = 0; H19 < 4; H19++) {
				for (int H20 = 0; H20 < 4; H20++) {
					if ((H4) * (4) + H19 < M) {
						if ((H3) * (4) + H20 < N) {
							u_int8_t tmp7 = 0;
							u_int8_t tmp8 = 0;
							if (0 <= (H3) * (4) + H20 - (1)) {
								tmp8 = x[(((4)) * (H20)) + H19];
							}
							u_int8_t tmp9 = 0;
							if ((H4) * (4) + H19 < M) {
								tmp9 = x[(((4)) * (H20 + 1)) + H19];
							}
							tmp7 = tmp8 + tmp9;
							u_int8_t tmp10 = 0;
							if ((H3) * (4) + H20 + 1 < N) {
								tmp10 = x[(((4)) * (H20 + 2)) + H19];
							}
							output[(M) * ((4) * (H3) + H20) + (4) * (H4) + H19] = tmp7 + tmp10;
						}
					}
				}
			}
		}
	}
	free(tmp2);
}

