#include <stdlib.h>
#include "blurtiles.h"

void blurtiles(float* v,int M,int N,float*output){
	float* tmp2 = (float*) aligned_alloc(4,(((1 + 5 - (1)) + 6 - (5))) * (4) * sizeof (float));
	for (int H3 = 0; H3 < ((N) + (4) - 1 ) / (4); H3++) {
		for (int H4 = 0; H4 < ((M) + (4) - 1 ) / (4); H4++) {
			for (int H8 = 0; H8 < 1; H8++) {
				for (int H9 = 0; H9 < 4; H9++) {
					if (0 <= (H3) * (4) + H8 - (1) && (H3) * (4) + H8 - (1) < N) {
						float tmp3 = 0;
						float tmp4 = 0;
						if (0 <= (H4) * (4) + H9 - (1) && (H4) * (4) + H9 - (1) < M) {
							tmp4 = v[(((M)) * ((H3) * (4) + H8 - (1))) + (H4) * (4) + H9 - (1)];
						}
						float tmp5 = 0;
						if ((H4) * (4) + H9 < M) {
							tmp5 = v[(((M)) * ((H3) * (4) + H8 - (1))) + (H4) * (4) + H9];
						}
						tmp3 = tmp4 + tmp5;
						float tmp6 = 0;
						if ((H4) * (4) + H9 + 1 < M) {
							tmp6 = v[(((M)) * ((H3) * (4) + H8 - (1))) + (H4) * (4) + H9 + 1];
						}
						tmp2[(4) * (H8) + H9] = tmp3 + tmp6;
					}
				}
			}
			for (int H21 = 1; H21 < 5; H21++) {
				for (int H22 = 0; H22 < 4; H22++) {
					if (0 <= (H3) * (4) + H21 - (1) && (H3) * (4) + H21 - (1) < N) {
						float tmp7 = 0;
						float tmp8 = 0;
						if (0 <= (H4) * (4) + H22 - (1) && (H4) * (4) + H22 - (1) < M) {
							tmp8 = v[(((M)) * ((H3) * (4) + H21 - (1))) + (H4) * (4) + H22 - (1)];
						}
						float tmp9 = 0;
						if ((H4) * (4) + H22 < M) {
							tmp9 = v[(((M)) * ((H3) * (4) + H21 - (1))) + (H4) * (4) + H22];
						}
						tmp7 = tmp8 + tmp9;
						float tmp10 = 0;
						if ((H4) * (4) + H22 + 1 < M) {
							tmp10 = v[(((M)) * ((H3) * (4) + H21 - (1))) + (H4) * (4) + H22 + 1];
						}
						tmp2[(4) * ((H21 - (1))) + H22 + (1) * (4)] = tmp7 + tmp10;
					}
				}
			}
			for (int H34 = 5; H34 < 6; H34++) {
				for (int H35 = 0; H35 < 4; H35++) {
					if (0 <= (H3) * (4) + H34 - (1) && (H3) * (4) + H34 - (1) < N) {
						float tmp11 = 0;
						float tmp12 = 0;
						if (0 <= (H4) * (4) + H35 - (1) && (H4) * (4) + H35 - (1) < M) {
							tmp12 = v[(((M)) * ((H3) * (4) + H34 - (1))) + (H4) * (4) + H35 - (1)];
						}
						float tmp13 = 0;
						if ((H4) * (4) + H35 < M) {
							tmp13 = v[(((M)) * ((H3) * (4) + H34 - (1))) + (H4) * (4) + H35];
						}
						tmp11 = tmp12 + tmp13;
						float tmp14 = 0;
						if ((H4) * (4) + H35 + 1 < M) {
							tmp14 = v[(((M)) * ((H3) * (4) + H34 - (1))) + (H4) * (4) + H35 + 1];
						}
						tmp2[(4) * ((H34 - (5))) + H35 + ((1 + 5 - (1))) * (4)] = tmp11 + tmp14;
					}
				}
			}
			float* x = tmp2;
			for (int H47 = 0; H47 < 4; H47++) {
				for (int H48 = 0; H48 < 4; H48++) {
					if ((H4) * (4) + H47 < M) {
						if ((H3) * (4) + H48 < N) {
							float tmp15 = 0;
							float tmp16 = 0;
							tmp16 = x[(((4)) * (H48)) + H47];
							float tmp17 = 0;
							tmp17 = x[(((4)) * (H48 + 1)) + H47];
							tmp15 = tmp16 + tmp17;
							float tmp18 = 0;
							if ((H3) * (4) + H48 + 1 < N) {
								tmp18 = x[(((4)) * (H48 + 2)) + H47];
							}
							output[(M) * ((4) * (H3) + H48) + (4) * (H4) + H47] = tmp15 + tmp18;
						}
					}
				}
			}
		}
	}
	free(tmp2);
}

