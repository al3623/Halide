#include <stdlib.h>
#include "conv1.h"

void conv1(int m,int n,float* c,float*output){
	for (int H4 = 0; H4 < n; H4++) {
		for (int H5 = 0; H5 < m; H5++) {
			float tmp2 = 0;
			if (0 <= H4 - (H5)) {
				float tmp3 = 0;
				float* tmp4 = (float*) calloc(1,((n - ((-(m)) + 1))) * sizeof (float));
				for (int H9 = (-(m)) + 1; H9 < n; H9++) {
					if (H9 == 2 + (-(m)) + 1) {
						tmp4[(H9 - ((-(m)) + 1))] = 1;
					}
				}
				tmp3 = tmp4[H4 - (H5)];
				free(tmp4);
				float tmp5 = 0;
				tmp5 = c[H5];
				tmp2 = tmp3 * tmp5;
			}
			output[H4] = output[H4] + tmp2;
		}
	}
}

