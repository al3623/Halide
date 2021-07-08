#include <stdlib.h>
#include "tile_nb.h"

void tile_nb(float* l,int m,int n,float*output){
#pragma omp parallel for
	for (int H34 = 0; H34 < (((n - (1 + 0)) - (1)) / (64)); H34++) {
		for (int H46 = 0; H46 < ((((m - (1 + 0)) - (1 + 0))) / (64)); H46++) {
			float* tmp2 = (float*) calloc(1,(66) * (64) * sizeof (float));
			for (int H49 = 0; H49 < 66; H49++) {
				for (int H50 = 0; H50 < 64; H50++) {
					float tmp3 = 0;
					float tmp4 = 0;
					tmp4 = l[(((m)) * ((H34) * (64) + H49)) + (H46) * (64) + H50];
					float tmp5 = 0;
					tmp5 = l[(((m)) * ((H34) * (64) + H49)) + 1 + (H46) * (64) + H50];
					tmp3 = tmp4 + tmp5;
					float tmp6 = 0;
					tmp6 = l[(((m)) * ((H34) * (64) + H49)) + 2 + (H46) * (64) + H50];
					tmp2[(64) * (H49) + H50] = tmp3 + tmp6;
				}
			}
			float* x4 = tmp2;
			for (int H52 = 0; H52 < 64; H52++) {
				for (int H53 = 0; H53 < 64; H53++) {
					float tmp7 = 0;
					float tmp8 = 0;
					tmp8 = x4[(((64)) * (H53)) + H52];
					float tmp9 = 0;
					tmp9 = x4[(((64)) * (H53 + 1)) + H52];
					tmp7 = tmp8 + tmp9;
					float tmp10 = 0;
					tmp10 = x4[(((64)) * (H53 + 2)) + H52];
					output[(((m - (1 + 0)) - (1 + 0))) * ((64) * (H34) + H53) + (64) * (H46) + H52] = tmp7 + tmp10;
				}
			}
			free(tmp2);
		}
		for (int H72 = ((((m - (1 + 0)) - (1 + 0))) / (64)); H72 < ((((m - (1 + 0)) - (1 + 0))) / (64)) + ((((((m - (1 + 0)) - (1 + 0))) % (64))) + (64) - 1 ) / (64); H72++) {
			for (int H73 = 0; H73 < 64; H73++) {
				for (int H74 = 0; H74 < 64; H74++) {
					if ((H72) * (64) + H73 < ((m - (1 + 0)) - (1 + 0))) {
						if ((H34) * (64) + H74 < (n - (1 + 0)) - (1)) {
							float tmp11 = 0;
							float tmp12 = 0;
							float tmp13 = 0;
							float tmp14 = 0;
							tmp14 = l[(((m)) * (1 + (H34) * (64) + H74 - (1))) + 1 + (H72) * (64) + H73 - (1)];
							float tmp15 = 0;
							tmp15 = l[(((m)) * (1 + (H34) * (64) + H74 - (1))) + 1 + (H72) * (64) + H73];
							tmp13 = tmp14 + tmp15;
							float tmp16 = 0;
							tmp16 = l[(((m)) * (1 + (H34) * (64) + H74 - (1))) + 1 + (H72) * (64) + H73 + 1];
							tmp12 = tmp13 + tmp16;
							float tmp17 = 0;
							float tmp18 = 0;
							float tmp19 = 0;
							tmp19 = l[(((m)) * (1 + (H34) * (64) + H74)) + 1 + (H72) * (64) + H73 - (1)];
							float tmp20 = 0;
							tmp20 = l[(((m)) * (1 + (H34) * (64) + H74)) + 1 + (H72) * (64) + H73];
							tmp18 = tmp19 + tmp20;
							float tmp21 = 0;
							tmp21 = l[(((m)) * (1 + (H34) * (64) + H74)) + 1 + (H72) * (64) + H73 + 1];
							tmp17 = tmp18 + tmp21;
							tmp11 = tmp12 + tmp17;
							float tmp22 = 0;
							float tmp23 = 0;
							float tmp24 = 0;
							tmp24 = l[(((m)) * (1 + (H34) * (64) + H74 + 1)) + 1 + (H72) * (64) + H73 - (1)];
							float tmp25 = 0;
							tmp25 = l[(((m)) * (1 + (H34) * (64) + H74 + 1)) + 1 + (H72) * (64) + H73];
							tmp23 = tmp24 + tmp25;
							float tmp26 = 0;
							tmp26 = l[(((m)) * (1 + (H34) * (64) + H74 + 1)) + 1 + (H72) * (64) + H73 + 1];
							tmp22 = tmp23 + tmp26;
							output[(((m - (1 + 0)) - (1 + 0))) * ((64) * (H34) + H74) + (64) * (((H72 - (((((m - (1 + 0)) - (1 + 0))) / (64)))) + ((((m - (1 + 0)) - (1 + 0))) / (64)))) + H73] = tmp11 + tmp22;
						}
					}
				}
			}
		}
	}
#pragma omp parallel for
	for (int H75 = (((n - (1 + 0)) - (1)) / (64)); H75 < (((n - (1 + 0)) - (1)) / (64)) + (((((n - (1 + 0)) - (1)) % (64))) + (64) - 1 ) / (64); H75++) {
		for (int H76 = 0; H76 < ((((m - (1 + 0)) - (1 + 0))) / (64)) + ((((((m - (1 + 0)) - (1 + 0))) % (64))) + (64) - 1 ) / (64); H76++) {
			for (int H77 = 0; H77 < 64; H77++) {
				for (int H78 = 0; H78 < 64; H78++) {
					if ((H76) * (64) + H77 < ((m - (1 + 0)) - (1 + 0))) {
						if ((H75) * (64) + H78 < (n - (1 + 0)) - (1)) {
							float tmp27 = 0;
							float tmp28 = 0;
							float tmp29 = 0;
							float tmp30 = 0;
							tmp30 = l[(((m)) * (1 + (H75) * (64) + H78 - (1))) + 1 + (H76) * (64) + H77 - (1)];
							float tmp31 = 0;
							tmp31 = l[(((m)) * (1 + (H75) * (64) + H78 - (1))) + 1 + (H76) * (64) + H77];
							tmp29 = tmp30 + tmp31;
							float tmp32 = 0;
							tmp32 = l[(((m)) * (1 + (H75) * (64) + H78 - (1))) + 1 + (H76) * (64) + H77 + 1];
							tmp28 = tmp29 + tmp32;
							float tmp33 = 0;
							float tmp34 = 0;
							float tmp35 = 0;
							tmp35 = l[(((m)) * (1 + (H75) * (64) + H78)) + 1 + (H76) * (64) + H77 - (1)];
							float tmp36 = 0;
							tmp36 = l[(((m)) * (1 + (H75) * (64) + H78)) + 1 + (H76) * (64) + H77];
							tmp34 = tmp35 + tmp36;
							float tmp37 = 0;
							tmp37 = l[(((m)) * (1 + (H75) * (64) + H78)) + 1 + (H76) * (64) + H77 + 1];
							tmp33 = tmp34 + tmp37;
							tmp27 = tmp28 + tmp33;
							float tmp38 = 0;
							float tmp39 = 0;
							float tmp40 = 0;
							tmp40 = l[(((m)) * (1 + (H75) * (64) + H78 + 1)) + 1 + (H76) * (64) + H77 - (1)];
							float tmp41 = 0;
							tmp41 = l[(((m)) * (1 + (H75) * (64) + H78 + 1)) + 1 + (H76) * (64) + H77];
							tmp39 = tmp40 + tmp41;
							float tmp42 = 0;
							tmp42 = l[(((m)) * (1 + (H75) * (64) + H78 + 1)) + 1 + (H76) * (64) + H77 + 1];
							tmp38 = tmp39 + tmp42;
							output[(((m - (1 + 0)) - (1 + 0))) * ((64) * (((H75 - ((((n - (1 + 0)) - (1)) / (64)))) + (((n - (1 + 0)) - (1)) / (64)))) + H78) + (64) * (H76) + H77] = tmp27 + tmp38;
						}
					}
				}
			}
		}
	}
}

