#include <stdlib.h>
#include "concattest1.h"

void concattest1(float* l,int m,int n,float*output){
#pragma omp parallel for
	for (int H14 = 0; H14 < 1; H14++) {
		for (int H15 = 0; H15 < n; H15++) {
			output[((1 + (m - (1)))) * (H15) + H14] = l[(((m)) * (H15)) + H14];
		}
	}
#pragma omp parallel for
	for (int H16 = 1; H16 < m; H16++) {
		for (int H25 = 0; H25 < 1; H25++) {
			output[((1 + (m - (1)))) * (H25) + ((H16 - (1)) + 1)] = l[(((m)) * (H25)) + H16];
		}
		for (int H26 = 1; H26 < n - (1); H26++) {
			output[((1 + (m - (1)))) * (((H26 - (1)) + 1)) + ((H16 - (1)) + 1)] = l[(((m)) * (H26)) + H16];
		}
		for (int H27 = n - (1); H27 < n; H27++) {
			output[((1 + (m - (1)))) * (((H27 - (n - (1))) + (1 + (n - (1) - (1))))) + ((H16 - (1)) + 1)] = l[(((m)) * (H27)) + H16];
		}
	}
}

