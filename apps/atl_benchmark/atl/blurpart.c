#include <stdlib.h>
#include "blurpart.h"

void blurpart(u_int8_t* v,int m,int n,u_int8_t*output){
	for (int H5 = 0; H5 < 1; H5++) {
		for (int H6 = 0; H6 < m; H6++) {
			u_int8_t tmp2 = 0;
			u_int8_t tmp3 = 0;
			if (0 <= H5 - (1)) {
				u_int8_t tmp4 = 0;
				u_int8_t tmp5 = 0;
				if (0 <= H6 - (1)) {
					tmp5 = v[(((m)) * (H5 - (1))) + H6 - (1)];
				}
				u_int8_t tmp6 = 0;
				tmp6 = v[(((m)) * (H5 - (1))) + H6];
				tmp4 = tmp5 + tmp6;
				u_int8_t tmp7 = 0;
				if (H6 + 1 < m) {
					tmp7 = v[(((m)) * (H5 - (1))) + H6 + 1];
				}
				tmp3 = tmp4 + tmp7;
			}
			u_int8_t tmp8 = 0;
			u_int8_t tmp9 = 0;
			u_int8_t tmp10 = 0;
			if (0 <= H6 - (1)) {
				tmp10 = v[(((m)) * (H5)) + H6 - (1)];
			}
			u_int8_t tmp11 = 0;
			tmp11 = v[(((m)) * (H5)) + H6];
			tmp9 = tmp10 + tmp11;
			u_int8_t tmp12 = 0;
			if (H6 + 1 < m) {
				tmp12 = v[(((m)) * (H5)) + H6 + 1];
			}
			tmp8 = tmp9 + tmp12;
			tmp2 = tmp3 + tmp8;
			u_int8_t tmp13 = 0;
			u_int8_t tmp14 = 0;
			u_int8_t tmp15 = 0;
			if (0 <= H6 - (1)) {
				tmp15 = v[(((m)) * (H5 + 1)) + H6 - (1)];
			}
			u_int8_t tmp16 = 0;
			tmp16 = v[(((m)) * (H5 + 1)) + H6];
			tmp14 = tmp15 + tmp16;
			u_int8_t tmp17 = 0;
			if (H6 + 1 < m) {
				tmp17 = v[(((m)) * (H5 + 1)) + H6 + 1];
			}
			tmp13 = tmp14 + tmp17;
			output[(m) * (H5) + H6] = tmp2 + tmp13;
		}
	}
	for (int H42 = 1; H42 < (n - 1); H42++) {
		for (int H45 = 0; H45 < 1; H45++) {
			u_int8_t tmp18 = 0;
			u_int8_t tmp19 = 0;
			u_int8_t tmp20 = 0;
			u_int8_t tmp21 = 0;
			if (0 <= H45 - (1)) {
				tmp21 = v[(((m)) * (H42 - (1))) + H45 - (1)];
			}
			u_int8_t tmp22 = 0;
			tmp22 = v[(((m)) * (H42 - (1))) + H45];
			tmp20 = tmp21 + tmp22;
			u_int8_t tmp23 = 0;
			tmp23 = v[(((m)) * (H42 - (1))) + H45 + 1];
			tmp19 = tmp20 + tmp23;
			u_int8_t tmp24 = 0;
			u_int8_t tmp25 = 0;
			u_int8_t tmp26 = 0;
			if (0 <= H45 - (1)) {
				tmp26 = v[(((m)) * (H42)) + H45 - (1)];
			}
			u_int8_t tmp27 = 0;
			tmp27 = v[(((m)) * (H42)) + H45];
			tmp25 = tmp26 + tmp27;
			u_int8_t tmp28 = 0;
			tmp28 = v[(((m)) * (H42)) + H45 + 1];
			tmp24 = tmp25 + tmp28;
			tmp18 = tmp19 + tmp24;
			u_int8_t tmp29 = 0;
			u_int8_t tmp30 = 0;
			u_int8_t tmp31 = 0;
			if (0 <= H45 - (1)) {
				tmp31 = v[(((m)) * (H42 + 1)) + H45 - (1)];
			}
			u_int8_t tmp32 = 0;
			tmp32 = v[(((m)) * (H42 + 1)) + H45];
			tmp30 = tmp31 + tmp32;
			u_int8_t tmp33 = 0;
			tmp33 = v[(((m)) * (H42 + 1)) + H45 + 1];
			tmp29 = tmp30 + tmp33;
			output[((((1 + (m - 1) - (1)) + m - (m - (1))))) * ((H42 - (1))) + H45 + (1) * (m)] = tmp18 + tmp29;
		}
		for (int H81 = 1; H81 < (m - 1); H81++) {
			u_int8_t tmp34 = 0;
			u_int8_t tmp35 = 0;
			u_int8_t tmp36 = 0;
			u_int8_t tmp37 = 0;
			tmp37 = v[(((m)) * (H42 - (1))) + H81 - (1)];
			u_int8_t tmp38 = 0;
			tmp38 = v[(((m)) * (H42 - (1))) + H81];
			tmp36 = tmp37 + tmp38;
			u_int8_t tmp39 = 0;
			tmp39 = v[(((m)) * (H42 - (1))) + H81 + 1];
			tmp35 = tmp36 + tmp39;
			u_int8_t tmp40 = 0;
			u_int8_t tmp41 = 0;
			u_int8_t tmp42 = 0;
			tmp42 = v[(((m)) * (H42)) + H81 - (1)];
			u_int8_t tmp43 = 0;
			tmp43 = v[(((m)) * (H42)) + H81];
			tmp41 = tmp42 + tmp43;
			u_int8_t tmp44 = 0;
			tmp44 = v[(((m)) * (H42)) + H81 + 1];
			tmp40 = tmp41 + tmp44;
			tmp34 = tmp35 + tmp40;
			u_int8_t tmp45 = 0;
			u_int8_t tmp46 = 0;
			u_int8_t tmp47 = 0;
			tmp47 = v[(((m)) * (H42 + 1)) + H81 - (1)];
			u_int8_t tmp48 = 0;
			tmp48 = v[(((m)) * (H42 + 1)) + H81];
			tmp46 = tmp47 + tmp48;
			u_int8_t tmp49 = 0;
			tmp49 = v[(((m)) * (H42 + 1)) + H81 + 1];
			tmp45 = tmp46 + tmp49;
			output[((((1 + (m - 1) - (1)) + m - (m - (1))))) * ((H42 - (1))) + (H81 - (1)) + (1) * (m) + (1)] = tmp34 + tmp45;
		}
		for (int H117 = m - (1); H117 < m; H117++) {
			u_int8_t tmp50 = 0;
			u_int8_t tmp51 = 0;
			u_int8_t tmp52 = 0;
			u_int8_t tmp53 = 0;
			u_int8_t tmp54 = 0;
			tmp54 = v[(((m)) * (H42 - (1))) + H117 - (1)];
			u_int8_t tmp55 = 0;
			tmp55 = v[(((m)) * (H42 - (1))) + H117];
			tmp53 = tmp54 + tmp55;
			u_int8_t tmp56 = 0;
			if (H117 + 1 < m) {
				tmp56 = v[(((m)) * (H42 - (1))) + H117 + 1];
			}
			tmp52 = tmp53 + tmp56;
			u_int8_t tmp57 = 0;
			u_int8_t tmp58 = 0;
			u_int8_t tmp59 = 0;
			tmp59 = v[(((m)) * (H42)) + H117 - (1)];
			u_int8_t tmp60 = 0;
			tmp60 = v[(((m)) * (H42)) + H117];
			tmp58 = tmp59 + tmp60;
			u_int8_t tmp61 = 0;
			if (H117 + 1 < m) {
				tmp61 = v[(((m)) * (H42)) + H117 + 1];
			}
			tmp57 = tmp58 + tmp61;
			tmp51 = tmp52 + tmp57;
			u_int8_t tmp62 = 0;
			u_int8_t tmp63 = 0;
			tmp63 = v[(((m)) * (H42 + 1)) + H117 - (1)];
			u_int8_t tmp64 = 0;
			tmp64 = v[(((m)) * (H42 + 1)) + H117];
			tmp62 = tmp63 + tmp64;
			tmp50 = tmp51 + tmp62;
			u_int8_t tmp65 = 0;
			if (H117 + 1 < m) {
				tmp65 = v[(((m)) * (H42 + 1)) + H117 + 1];
			}
			output[((((1 + (m - 1) - (1)) + m - (m - (1))))) * ((H42 - (1))) + (H117 - (m - (1))) + (1) * (m) + ((1 + (m - 1) - (1)))] = tmp50 + tmp65;
		}
	}
	for (int H153 = n - (1); H153 < n; H153++) {
		for (int H154 = 0; H154 < m; H154++) {
			u_int8_t tmp66 = 0;
			u_int8_t tmp67 = 0;
			u_int8_t tmp68 = 0;
			u_int8_t tmp69 = 0;
			if (0 <= H154 - (1)) {
				tmp69 = v[(((m)) * (H153 - (1))) + H154 - (1)];
			}
			u_int8_t tmp70 = 0;
			tmp70 = v[(((m)) * (H153 - (1))) + H154];
			tmp68 = tmp69 + tmp70;
			u_int8_t tmp71 = 0;
			if (H154 + 1 < m) {
				tmp71 = v[(((m)) * (H153 - (1))) + H154 + 1];
			}
			tmp67 = tmp68 + tmp71;
			u_int8_t tmp72 = 0;
			u_int8_t tmp73 = 0;
			u_int8_t tmp74 = 0;
			if (0 <= H154 - (1)) {
				tmp74 = v[(((m)) * (H153)) + H154 - (1)];
			}
			u_int8_t tmp75 = 0;
			tmp75 = v[(((m)) * (H153)) + H154];
			tmp73 = tmp74 + tmp75;
			u_int8_t tmp76 = 0;
			if (H154 + 1 < m) {
				tmp76 = v[(((m)) * (H153)) + H154 + 1];
			}
			tmp72 = tmp73 + tmp76;
			tmp66 = tmp67 + tmp72;
			u_int8_t tmp77 = 0;
			if (H153 + 1 < n) {
				u_int8_t tmp78 = 0;
				u_int8_t tmp79 = 0;
				if (0 <= H154 - (1)) {
					tmp79 = v[(((m)) * (H153 + 1)) + H154 - (1)];
				}
				u_int8_t tmp80 = 0;
				tmp80 = v[(((m)) * (H153 + 1)) + H154];
				tmp78 = tmp79 + tmp80;
				u_int8_t tmp81 = 0;
				if (H154 + 1 < m) {
					tmp81 = v[(((m)) * (H153 + 1)) + H154 + 1];
				}
				tmp77 = tmp78 + tmp81;
			}
			output[(m) * ((H153 - (n - (1)))) + H154 + ((1 + (n - 1) - (1))) * (m)] = tmp66 + tmp77;
		}
	}
}

