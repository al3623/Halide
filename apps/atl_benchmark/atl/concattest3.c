#include <stdlib.h>
#include "concattest3.h"

void concattest3(float* l,int m,int n,float*output){
#pragma omp parallel for
	for (int H3 = 0; H3 < m; H3++) {
		for (int H7 = 0; H7 < 1; H7++) {
			output[(m) * (H7) + H3] = l[(((m)) * (H7)) + H3];
		}
		for (int H8 = 1; H8 < n; H8++) {
			output[(m) * (((H8 - (1)) + 1)) + H3] = l[(((m)) * (H8)) + H3];
		}
	}
}

