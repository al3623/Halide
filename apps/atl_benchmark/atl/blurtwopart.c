#include <stdlib.h>
#include "blurtwopart.h"

void blurtwopart(u_int8_t* v,int M,int N,u_int8_t*output){
	v = (u_int8_t *) __builtin_assume_aligned (v, 4);
	output = (u_int8_t *) __builtin_assume_aligned (output, 4);
	N = N & 0xFFFFFFFC; 
	M = M & 0xFFFFFFFC; 
	u_int8_t* tmp2 = (u_int8_t*) aligned_alloc(4,(((1 + (N + 1) - (1)) + N + 2 - (N + 1))) * (M) * sizeof (u_int8_t));
	//u_int8_t* tmp2 = (u_int8_t*) calloc(1,(((1 + (N + 1) - (1)) + N + 2 - (N + 1))) * (M) * sizeof (u_int8_t));
	for (int H6 = 0; H6 < 1; H6++) {
		for (int H7 = 0; H7 < M; H7++) {
			tmp2[(M) * (H6) + H7] = 0;
		}
	}
	for (int H9 = 1; H9 < (N + 1); H9++) {
		for (int H12 = 0; H12 < 1; H12++) {
			u_int8_t tmp3 = 0;
			tmp3 = v[(((M)) * (H9 - (1))) + H12];
			u_int8_t tmp4 = 0;
			tmp4 = v[(((M)) * (H9 - (1))) + H12 + 1];
			tmp2[((((1 + (M - 1) - (1)) + M - (M - (1))))) * ((H9 - (1))) + H12 + (1) * (M)] = tmp3 + tmp4;
		}
		for (int H20 = 1; H20 < (M - 1); H20++) {
			u_int8_t tmp5 = 0;
			u_int8_t tmp6 = 0;
			tmp6 = v[(((M)) * (H9 - (1))) + H20 - (1)];
			u_int8_t tmp7 = 0;
			tmp7 = v[(((M)) * (H9 - (1))) + H20];
			tmp5 = tmp6 + tmp7;
			u_int8_t tmp8 = 0;
			tmp8 = v[(((M)) * (H9 - (1))) + H20 + 1];
			tmp2[((((1 + (M - 1) - (1)) + M - (M - (1))))) * ((H9 - (1))) + (H20 - (1)) + (1) * (M) + (1)] = tmp5 + tmp8;
		}
		for (int H32 = M - (1); H32 < M; H32++) {
			u_int8_t tmp9 = 0;
			tmp9 = v[(((M)) * (H9 - (1))) + H32 - (1)];
			u_int8_t tmp10 = 0;
			tmp10 = v[(((M)) * (H9 - (1))) + H32];
			tmp2[((((1 + (M - 1) - (1)) + M - (M - (1))))) * ((H9 - (1))) + (H32 - (M - (1))) + (1) * (M) + ((1 + (M - 1) - (1)))] = tmp9 + tmp10;
		}
	}
	for (int H40 = N + 1; H40 < N + 2; H40++) {
		for (int H41 = 0; H41 < M; H41++) {
			tmp2[(M) * ((H40 - (N + 1))) + H41 + ((1 + (N + 1) - (1))) * (M)] = 0;
		}
	}
	u_int8_t* x = tmp2;
	for (int H43 = 0; H43 < N; H43++) {
		for (int H44 = 0; H44 < M; H44++) {
			u_int8_t tmp11 = 0;
			u_int8_t tmp12 = 0;
			tmp12 = x[(((M)) * (H43)) + H44];
			u_int8_t tmp13 = 0;
			tmp13 = x[(((M)) * (H43 + 1)) + H44];
			tmp11 = tmp12 + tmp13;
			u_int8_t tmp14 = 0;
			tmp14 = x[(((M)) * (H43 + 2)) + H44];
			output[(M) * (H43) + H44] = tmp11 + tmp14;
		}
	}
	free(tmp2);
}

