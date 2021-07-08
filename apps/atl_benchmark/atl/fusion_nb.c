#include <stdlib.h>
#include "fusion_nb.h"

void fusion_nb(float* l,int m,int n,float*output){
#pragma omp parallel for
	for (int H4 = 1; H4 < (n - (1 + 0)); H4++) {
		for (int H5 = 1; H5 < (m - (1 + 0)); H5++) {
			float tmp2 = 0;
			float tmp3 = 0;
			float tmp4 = 0;
			float tmp5 = 0;
			tmp5 = l[(((m)) * (H4 - (1))) + H5 - (1)];
			float tmp6 = 0;
			tmp6 = l[(((m)) * (H4 - (1))) + H5];
			tmp4 = tmp5 + tmp6;
			float tmp7 = 0;
			tmp7 = l[(((m)) * (H4 - (1))) + H5 + 1];
			tmp3 = tmp4 + tmp7;
			float tmp8 = 0;
			float tmp9 = 0;
			float tmp10 = 0;
			tmp10 = l[(((m)) * (H4)) + H5 - (1)];
			float tmp11 = 0;
			tmp11 = l[(((m)) * (H4)) + H5];
			tmp9 = tmp10 + tmp11;
			float tmp12 = 0;
			tmp12 = l[(((m)) * (H4)) + H5 + 1];
			tmp8 = tmp9 + tmp12;
			tmp2 = tmp3 + tmp8;
			float tmp13 = 0;
			float tmp14 = 0;
			float tmp15 = 0;
			tmp15 = l[(((m)) * (H4 + 1)) + H5 - (1)];
			float tmp16 = 0;
			tmp16 = l[(((m)) * (H4 + 1)) + H5];
			tmp14 = tmp15 + tmp16;
			float tmp17 = 0;
			tmp17 = l[(((m)) * (H4 + 1)) + H5 + 1];
			tmp13 = tmp14 + tmp17;
			output[(((m - (1 + 0)) - 1)) * ((H4 - (1))) + (H5 - (1))] = tmp2 + tmp13;
		}
	}
}

