#include <stdlib.h>
#include "blurtwopart.h"

void blurtwopart(float* v,int M,int N,float*output){
	float* tmp2 = (float*) calloc(1,(((1 + ((N + 1 + 0) - (1))) + (N + 2 - (N + 1)))) * (M) * sizeof (float));
	for (int H35 = 0; H35 < 1; H35++) {
		for (int H36 = 0; H36 < M; H36++) {
			tmp2[(M) * (H35) + H36] = 0;
		}
	}
	for (int H37 = 1; H37 < (N + 1 + 0); H37++) {
		for (int H46 = 0; H46 < 1; H46++) {
			float tmp3 = 0;
			tmp3 = v[(((M)) * (H37 - (1))) + H46];
			float tmp4 = 0;
			tmp4 = v[(((M)) * (H37 - (1))) + H46 + 1];
			tmp2[(((1 + ((M - (1 + 0)) - (1))) + (M - (M - (1))))) * (((H37 - (1)) + 1)) + H46] = tmp3 + tmp4;
		}
		for (int H47 = 1; H47 < (M - (1 + 0)); H47++) {
			float tmp5 = 0;
			float tmp6 = 0;
			tmp6 = v[(((M)) * (H37 - (1))) + H47 - (1)];
			float tmp7 = 0;
			tmp7 = v[(((M)) * (H37 - (1))) + H47];
			tmp5 = tmp6 + tmp7;
			float tmp8 = 0;
			tmp8 = v[(((M)) * (H37 - (1))) + H47 + 1];
			tmp2[(((1 + ((M - (1 + 0)) - (1))) + (M - (M - (1))))) * (((H37 - (1)) + 1)) + ((H47 - (1)) + 1)] = tmp5 + tmp8;
		}
		for (int H48 = M - (1); H48 < M; H48++) {
			float tmp9 = 0;
			tmp9 = v[(((M)) * (H37 - (1))) + H48 - (1)];
			float tmp10 = 0;
			tmp10 = v[(((M)) * (H37 - (1))) + H48];
			tmp2[(((1 + ((M - (1 + 0)) - (1))) + (M - (M - (1))))) * (((H37 - (1)) + 1)) + ((H48 - (M - (1))) + (1 + ((M - (1 + 0)) - (1))))] = tmp9 + tmp10;
		}
	}
	for (int H49 = N + 1; H49 < N + 2; H49++) {
		for (int H50 = 0; H50 < M; H50++) {
			tmp2[(M) * (((H49 - (N + 1)) + (1 + ((N + 1 + 0) - (1))))) + H50] = 0;
		}
	}
	float* x0 = tmp2;
#pragma omp parallel for
	for (int H52 = 0; H52 < N; H52++) {
		for (int H53 = 0; H53 < M; H53++) {
			float tmp11 = 0;
			float tmp12 = 0;
			tmp12 = x0[(((M)) * (H52)) + H53];
			float tmp13 = 0;
			tmp13 = x0[(((M)) * (H52 + 1)) + H53];
			tmp11 = tmp12 + tmp13;
			float tmp14 = 0;
			tmp14 = x0[(((M)) * (H52 + 2)) + H53];
			output[(M) * (H52) + H53] = tmp11 + tmp14;
		}
	}
	free(tmp2);
}

