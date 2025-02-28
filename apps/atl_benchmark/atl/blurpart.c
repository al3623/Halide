#include <stdlib.h>
#include "blurpart.h"

void blurpart(float* v,int m,int n,float*output){
#pragma omp parallel for
	for (int H32 = 0; H32 < 1; H32++) {
		for (int H33 = 0; H33 < m; H33++) {
			float tmp2 = 0;
			float tmp3 = 0;
			if (0 <= H32 - (1)) {
				float tmp4 = 0;
				float tmp5 = 0;
				if (0 <= H33 - (1)) {
					tmp5 = v[(((m)) * (H32 - (1))) + H33 - (1)];
				}
				float tmp6 = 0;
				tmp6 = v[(((m)) * (H32 - (1))) + H33];
				tmp4 = tmp5 + tmp6;
				float tmp7 = 0;
				if (H33 + 1 < m) {
					tmp7 = v[(((m)) * (H32 - (1))) + H33 + 1];
				}
				tmp3 = tmp4 + tmp7;
			}
			float tmp8 = 0;
			float tmp9 = 0;
			float tmp10 = 0;
			if (0 <= H33 - (1)) {
				tmp10 = v[(((m)) * (H32)) + H33 - (1)];
			}
			float tmp11 = 0;
			tmp11 = v[(((m)) * (H32)) + H33];
			tmp9 = tmp10 + tmp11;
			float tmp12 = 0;
			if (H33 + 1 < m) {
				tmp12 = v[(((m)) * (H32)) + H33 + 1];
			}
			tmp8 = tmp9 + tmp12;
			tmp2 = tmp3 + tmp8;
			float tmp13 = 0;
			float tmp14 = 0;
			float tmp15 = 0;
			if (0 <= H33 - (1)) {
				tmp15 = v[(((m)) * (H32 + 1)) + H33 - (1)];
			}
			float tmp16 = 0;
			tmp16 = v[(((m)) * (H32 + 1)) + H33];
			tmp14 = tmp15 + tmp16;
			float tmp17 = 0;
			if (H33 + 1 < m) {
				tmp17 = v[(((m)) * (H32 + 1)) + H33 + 1];
			}
			tmp13 = tmp14 + tmp17;
			output[(m) * (H32) + H33] = tmp2 + tmp13;
		}
	}
#pragma omp parallel for
	for (int H34 = 1; H34 < (n - (1 + 0)); H34++) {
		for (int H43 = 0; H43 < 1; H43++) {
			float tmp18 = 0;
			float tmp19 = 0;
			float tmp20 = 0;
			float tmp21 = 0;
			if (0 <= H43 - (1)) {
				tmp21 = v[(((m)) * (H34 - (1))) + H43 - (1)];
			}
			float tmp22 = 0;
			tmp22 = v[(((m)) * (H34 - (1))) + H43];
			tmp20 = tmp21 + tmp22;
			float tmp23 = 0;
			tmp23 = v[(((m)) * (H34 - (1))) + H43 + 1];
			tmp19 = tmp20 + tmp23;
			float tmp24 = 0;
			float tmp25 = 0;
			float tmp26 = 0;
			if (0 <= H43 - (1)) {
				tmp26 = v[(((m)) * (H34)) + H43 - (1)];
			}
			float tmp27 = 0;
			tmp27 = v[(((m)) * (H34)) + H43];
			tmp25 = tmp26 + tmp27;
			float tmp28 = 0;
			tmp28 = v[(((m)) * (H34)) + H43 + 1];
			tmp24 = tmp25 + tmp28;
			tmp18 = tmp19 + tmp24;
			float tmp29 = 0;
			float tmp30 = 0;
			float tmp31 = 0;
			if (0 <= H43 - (1)) {
				tmp31 = v[(((m)) * (H34 + 1)) + H43 - (1)];
			}
			float tmp32 = 0;
			tmp32 = v[(((m)) * (H34 + 1)) + H43];
			tmp30 = tmp31 + tmp32;
			float tmp33 = 0;
			tmp33 = v[(((m)) * (H34 + 1)) + H43 + 1];
			tmp29 = tmp30 + tmp33;
			output[(((1 + ((m - (1 + 0)) - (1))) + (m - (m - (1))))) * (((H34 - (1)) + 1)) + H43] = tmp18 + tmp29;
		}
		for (int H44 = 1; H44 < (m - (1 + 0)); H44++) {
			float tmp34 = 0;
			float tmp35 = 0;
			float tmp36 = 0;
			float tmp37 = 0;
			tmp37 = v[(((m)) * (H34 - (1))) + H44 - (1)];
			float tmp38 = 0;
			tmp38 = v[(((m)) * (H34 - (1))) + H44];
			tmp36 = tmp37 + tmp38;
			float tmp39 = 0;
			tmp39 = v[(((m)) * (H34 - (1))) + H44 + 1];
			tmp35 = tmp36 + tmp39;
			float tmp40 = 0;
			float tmp41 = 0;
			float tmp42 = 0;
			tmp42 = v[(((m)) * (H34)) + H44 - (1)];
			float tmp43 = 0;
			tmp43 = v[(((m)) * (H34)) + H44];
			tmp41 = tmp42 + tmp43;
			float tmp44 = 0;
			tmp44 = v[(((m)) * (H34)) + H44 + 1];
			tmp40 = tmp41 + tmp44;
			tmp34 = tmp35 + tmp40;
			float tmp45 = 0;
			float tmp46 = 0;
			float tmp47 = 0;
			tmp47 = v[(((m)) * (H34 + 1)) + H44 - (1)];
			float tmp48 = 0;
			tmp48 = v[(((m)) * (H34 + 1)) + H44];
			tmp46 = tmp47 + tmp48;
			float tmp49 = 0;
			tmp49 = v[(((m)) * (H34 + 1)) + H44 + 1];
			tmp45 = tmp46 + tmp49;
			output[(((1 + ((m - (1 + 0)) - (1))) + (m - (m - (1))))) * (((H34 - (1)) + 1)) + ((H44 - (1)) + 1)] = tmp34 + tmp45;
		}
		for (int H45 = m - (1); H45 < m; H45++) {
			float tmp50 = 0;
			float tmp51 = 0;
			float tmp52 = 0;
			float tmp53 = 0;
			float tmp54 = 0;
			tmp54 = v[(((m)) * (H34 - (1))) + H45 - (1)];
			float tmp55 = 0;
			tmp55 = v[(((m)) * (H34 - (1))) + H45];
			tmp53 = tmp54 + tmp55;
			float tmp56 = 0;
			if (H45 + 1 < m) {
				tmp56 = v[(((m)) * (H34 - (1))) + H45 + 1];
			}
			tmp52 = tmp53 + tmp56;
			float tmp57 = 0;
			float tmp58 = 0;
			float tmp59 = 0;
			tmp59 = v[(((m)) * (H34)) + H45 - (1)];
			float tmp60 = 0;
			tmp60 = v[(((m)) * (H34)) + H45];
			tmp58 = tmp59 + tmp60;
			float tmp61 = 0;
			if (H45 + 1 < m) {
				tmp61 = v[(((m)) * (H34)) + H45 + 1];
			}
			tmp57 = tmp58 + tmp61;
			tmp51 = tmp52 + tmp57;
			float tmp62 = 0;
			float tmp63 = 0;
			tmp63 = v[(((m)) * (H34 + 1)) + H45 - (1)];
			float tmp64 = 0;
			tmp64 = v[(((m)) * (H34 + 1)) + H45];
			tmp62 = tmp63 + tmp64;
			tmp50 = tmp51 + tmp62;
			float tmp65 = 0;
			if (H45 + 1 < m) {
				tmp65 = v[(((m)) * (H34 + 1)) + H45 + 1];
			}
			output[(((1 + ((m - (1 + 0)) - (1))) + (m - (m - (1))))) * (((H34 - (1)) + 1)) + ((H45 - (m - (1))) + (1 + ((m - (1 + 0)) - (1))))] = tmp50 + tmp65;
		}
	}
#pragma omp parallel for
	for (int H46 = n - (1); H46 < n; H46++) {
		for (int H47 = 0; H47 < m; H47++) {
			float tmp66 = 0;
			float tmp67 = 0;
			float tmp68 = 0;
			float tmp69 = 0;
			if (0 <= H47 - (1)) {
				tmp69 = v[(((m)) * (H46 - (1))) + H47 - (1)];
			}
			float tmp70 = 0;
			tmp70 = v[(((m)) * (H46 - (1))) + H47];
			tmp68 = tmp69 + tmp70;
			float tmp71 = 0;
			if (H47 + 1 < m) {
				tmp71 = v[(((m)) * (H46 - (1))) + H47 + 1];
			}
			tmp67 = tmp68 + tmp71;
			float tmp72 = 0;
			float tmp73 = 0;
			float tmp74 = 0;
			if (0 <= H47 - (1)) {
				tmp74 = v[(((m)) * (H46)) + H47 - (1)];
			}
			float tmp75 = 0;
			tmp75 = v[(((m)) * (H46)) + H47];
			tmp73 = tmp74 + tmp75;
			float tmp76 = 0;
			if (H47 + 1 < m) {
				tmp76 = v[(((m)) * (H46)) + H47 + 1];
			}
			tmp72 = tmp73 + tmp76;
			tmp66 = tmp67 + tmp72;
			float tmp77 = 0;
			if (H46 + 1 < n) {
				float tmp78 = 0;
				float tmp79 = 0;
				if (0 <= H47 - (1)) {
					tmp79 = v[(((m)) * (H46 + 1)) + H47 - (1)];
				}
				float tmp80 = 0;
				tmp80 = v[(((m)) * (H46 + 1)) + H47];
				tmp78 = tmp79 + tmp80;
				float tmp81 = 0;
				if (H47 + 1 < m) {
					tmp81 = v[(((m)) * (H46 + 1)) + H47 + 1];
				}
				tmp77 = tmp78 + tmp81;
			}
			output[(m) * (((H46 - (n - (1))) + (1 + ((n - (1 + 0)) - (1))))) + H47] = tmp66 + tmp77;
		}
	}
}

