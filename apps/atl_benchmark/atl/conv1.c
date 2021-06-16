#include <stdlib.h>
#include "conv1.h"

void conv1(int m,int n,u_int8_t* c,u_int8_t*output){
	u_int8_t* tmp4 = (u_int8_t*) calloc(1,(n - ((-(m)) + 1)) * sizeof (u_int8_t));
	for (int H3 = 0; H3 < n; H3++) {
		for (int H4 = 0; H4 < m; H4++) {
			u_int8_t tmp2 = 0;
			if (0 <= H3 - (H4)) {
				u_int8_t tmp3 = 0;
				for (int H9 = (-(m)) + 1; H9 < n; H9++) {
					if (H9 == 2 + (-(m)) + 1) {
						tmp4[(H9 - ((-(m)) + 1))] = 1;
					}
				}
				tmp3 = tmp4[H3 - (H4)];
				u_int8_t tmp5 = 0;
				tmp5 = c[H4];
				tmp2 = tmp3 * tmp5;
			}
			output[H3] = output[H3] + tmp2;
		}
	}
	free(tmp4);
}

