#include <stdlib.h>
#include "blurpart.h"

void blurpart(u_int8_t* v,int m,int n,u_int8_t*output){
	for (int H5 = 0; H5 < 1; H5++) {
		for (int H6 = 0; H6 < m; H6++) {
			u_int8_t tmp2 = 0;
			u_int8_t tmp3 = 0;
			u_int8_t tmp4 = 0;
			if (0 <= H6 - (1)) {
				tmp4 = v[(((m)) * (H5)) + H6 - (1)];
			}
			u_int8_t tmp5 = 0;
			tmp5 = v[(((m)) * (H5)) + H6];
			tmp3 = tmp4 + tmp5;
			u_int8_t tmp6 = 0;
			if (H6 + 1 < m) {
				tmp6 = v[(((m)) * (H5)) + H6 + 1];
			}
			tmp2 = tmp3 + tmp6;
			u_int8_t tmp7 = 0;
			u_int8_t tmp8 = 0;
			u_int8_t tmp9 = 0;
			if (0 <= H6 - (1)) {
				tmp9 = v[(((m)) * (H5 + 1)) + H6 - (1)];
			}
			u_int8_t tmp10 = 0;
			tmp10 = v[(((m)) * (H5 + 1)) + H6];
			tmp8 = tmp9 + tmp10;
			u_int8_t tmp11 = 0;
			if (H6 + 1 < m) {
				tmp11 = v[(((m)) * (H5 + 1)) + H6 + 1];
			}
			tmp7 = tmp8 + tmp11;
			output[(m) * (H5) + H6] = tmp2 + tmp7;
		}
	}
	for (int H30 = 1; H30 < (n - 1); H30++) {
		for (int H33 = 0; H33 < 1; H33++) {
			u_int8_t tmp12 = 0;
			u_int8_t tmp13 = 0;
			u_int8_t tmp14 = 0;
			tmp14 = v[(((m)) * (H30 - (1))) + H33];
			u_int8_t tmp15 = 0;
			tmp15 = v[(((m)) * (H30 - (1))) + H33 + 1];
			tmp13 = tmp14 + tmp15;
			u_int8_t tmp16 = 0;
			u_int8_t tmp17 = 0;
			tmp17 = v[(((m)) * (H30)) + H33];
			u_int8_t tmp18 = 0;
			tmp18 = v[(((m)) * (H30)) + H33 + 1];
			tmp16 = tmp17 + tmp18;
			tmp12 = tmp13 + tmp16;
			u_int8_t tmp19 = 0;
			u_int8_t tmp20 = 0;
			tmp20 = v[(((m)) * (H30 + 1)) + H33];
			u_int8_t tmp21 = 0;
			tmp21 = v[(((m)) * (H30 + 1)) + H33 + 1];
			tmp19 = tmp20 + tmp21;
			output[(m) * ((H30 - (1))) + H33 + (m)] = tmp12 + tmp19;
		}
		for (int H57 = 1; H57 < (m - 1); H57++) {
			u_int8_t tmp22 = 0;
			u_int8_t tmp23 = 0;
			u_int8_t tmp24 = 0;
			u_int8_t tmp25 = 0;
			tmp25 = v[(((m)) * (H30 - (1))) + H57 - (1)];
			u_int8_t tmp26 = 0;
			tmp26 = v[(((m)) * (H30 - (1))) + H57];
			tmp24 = tmp25 + tmp26;
			u_int8_t tmp27 = 0;
			tmp27 = v[(((m)) * (H30 - (1))) + H57 + 1];
			tmp23 = tmp24 + tmp27;
			u_int8_t tmp28 = 0;
			u_int8_t tmp29 = 0;
			u_int8_t tmp30 = 0;
			tmp30 = v[(((m)) * (H30)) + H57 - (1)];
			u_int8_t tmp31 = 0;
			tmp31 = v[(((m)) * (H30)) + H57];
			tmp29 = tmp30 + tmp31;
			u_int8_t tmp32 = 0;
			tmp32 = v[(((m)) * (H30)) + H57 + 1];
			tmp28 = tmp29 + tmp32;
			tmp22 = tmp23 + tmp28;
			u_int8_t tmp33 = 0;
			u_int8_t tmp34 = 0;
			u_int8_t tmp35 = 0;
			tmp35 = v[(((m)) * (H30 + 1)) + H57 - (1)];
			u_int8_t tmp36 = 0;
			tmp36 = v[(((m)) * (H30 + 1)) + H57];
			tmp34 = tmp35 + tmp36;
			u_int8_t tmp37 = 0;
			tmp37 = v[(((m)) * (H30 + 1)) + H57 + 1];
			tmp33 = tmp34 + tmp37;
			output[(m) * ((H30 - (1))) + (H57 - (1)) +(m) + (1)] = tmp22 + tmp33;
		}
		for (int H93 = m - (1); H93 < m; H93++) {
			u_int8_t tmp38 = 0;
			u_int8_t tmp39 = 0;
			u_int8_t tmp40 = 0;
			tmp40 = v[(((m)) * (H30 - (1))) + H93 - (1)];
			u_int8_t tmp41 = 0;
			tmp41 = v[(((m)) * (H30 - (1))) + H93];
			tmp39 = tmp40 + tmp41;
			u_int8_t tmp42 = 0;
			u_int8_t tmp43 = 0;
			tmp43 = v[(((m)) * (H30)) + H93 - (1)];
			u_int8_t tmp44 = 0;
			tmp44 = v[(((m)) * (H30)) + H93];
			tmp42 = tmp43 + tmp44;
			tmp38 = tmp39 + tmp42;
			u_int8_t tmp45 = 0;
			u_int8_t tmp46 = 0;
			tmp46 = v[(((m)) * (H30 + 1)) + H93 - (1)];
			u_int8_t tmp47 = 0;
			tmp47 = v[(((m)) * (H30 + 1)) + H93];
			tmp45 = tmp46 + tmp47;
			output[(m) * ((H30 - (1))) + (H93 - (m - (1))) + (m) + ((m - (1)))] = tmp38 + tmp45;
		}
	}
	for (int H117 = n - (1); H117 < n; H117++) {
		for (int H118 = 0; H118 < m; H118++) {
			u_int8_t tmp48 = 0;
			u_int8_t tmp49 = 0;
			u_int8_t tmp50 = 0;
			if (0 <= H118 - (1)) {
				tmp50 = v[(((m)) * (H117 - (1))) + H118 - (1)];
			}
			u_int8_t tmp51 = 0;
			tmp51 = v[(((m)) * (H117 - (1))) + H118];
			tmp49 = tmp50 + tmp51;
			u_int8_t tmp52 = 0;
			if (H118 + 1 < m) {
				tmp52 = v[(((m)) * (H117 - (1))) + H118 + 1];
			}
			tmp48 = tmp49 + tmp52;
			u_int8_t tmp53 = 0;
			u_int8_t tmp54 = 0;
			u_int8_t tmp55 = 0;
			if (0 <= H118 - (1)) {
				tmp55 = v[(((m)) * (H117)) + H118 - (1)];
			}
			u_int8_t tmp56 = 0;
			tmp56 = v[(((m)) * (H117)) + H118];
			tmp54 = tmp55 + tmp56;
			u_int8_t tmp57 = 0;
			if (H118 + 1 < m) {
				tmp57 = v[(((m)) * (H117)) + H118 + 1];
			}
			tmp53 = tmp54 + tmp57;
			output[(m) * ((H117 - (n - (1)))) + H118 + ((n - (1))) * (m)] = tmp48 + tmp53;
		}
	}
}

