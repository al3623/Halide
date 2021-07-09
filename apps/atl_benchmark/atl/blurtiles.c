#include <stdlib.h>
#include "blurtiles.h"

void blurtiles(float* l,int m,int n,float*output){
#pragma omp parallel for
	for (int H80 = 0; H80 < 1; H80++) {
		for (int H81 = 0; H81 < m; H81++) {
			float tmp2 = 0;
			float tmp3 = 0;
			if (0 <= H80 - (1)) {
				float tmp4 = 0;
				float tmp5 = 0;
				if (0 <= H81 - (1)) {
					tmp5 = l[(((m)) * (H80 - (1))) + H81 - (1)];
				}
				float tmp6 = 0;
				tmp6 = l[(((m)) * (H80 - (1))) + H81];
				tmp4 = tmp5 + tmp6;
				float tmp7 = 0;
				if (H81 + 1 < m) {
					tmp7 = l[(((m)) * (H80 - (1))) + H81 + 1];
				}
				tmp3 = tmp4 + tmp7;
			}
			float tmp8 = 0;
			float tmp9 = 0;
			float tmp10 = 0;
			if (0 <= H81 - (1)) {
				tmp10 = l[(((m)) * (H80)) + H81 - (1)];
			}
			float tmp11 = 0;
			tmp11 = l[(((m)) * (H80)) + H81];
			tmp9 = tmp10 + tmp11;
			float tmp12 = 0;
			if (H81 + 1 < m) {
				tmp12 = l[(((m)) * (H80)) + H81 + 1];
			}
			tmp8 = tmp9 + tmp12;
			tmp2 = tmp3 + tmp8;
			float tmp13 = 0;
			float tmp14 = 0;
			float tmp15 = 0;
			if (0 <= H81 - (1)) {
				tmp15 = l[(((m)) * (H80 + 1)) + H81 - (1)];
			}
			float tmp16 = 0;
			tmp16 = l[(((m)) * (H80 + 1)) + H81];
			tmp14 = tmp15 + tmp16;
			float tmp17 = 0;
			if (H81 + 1 < m) {
				tmp17 = l[(((m)) * (H80 + 1)) + H81 + 1];
			}
			tmp13 = tmp14 + tmp17;
			output[(m) * (H80) + H81] = tmp2 + tmp13;
		}
	}
#pragma omp parallel for
	for (int H128 = 1; H128 < (n - (1 + 0)); H128++) {
		for (int H129 = 0; H129 < 1; H129++) {
			float tmp18 = 0;
			float tmp19 = 0;
			float tmp20 = 0;
			float tmp21 = 0;
			if (0 <= H129 - (1)) {
				tmp21 = l[(((m)) * (H128 - (1))) + H129 - (1)];
			}
			float tmp22 = 0;
			tmp22 = l[(((m)) * (H128 - (1))) + H129];
			tmp20 = tmp21 + tmp22;
			float tmp23 = 0;
			tmp23 = l[(((m)) * (H128 - (1))) + H129 + 1];
			tmp19 = tmp20 + tmp23;
			float tmp24 = 0;
			float tmp25 = 0;
			float tmp26 = 0;
			if (0 <= H129 - (1)) {
				tmp26 = l[(((m)) * (H128)) + H129 - (1)];
			}
			float tmp27 = 0;
			tmp27 = l[(((m)) * (H128)) + H129];
			tmp25 = tmp26 + tmp27;
			float tmp28 = 0;
			tmp28 = l[(((m)) * (H128)) + H129 + 1];
			tmp24 = tmp25 + tmp28;
			tmp18 = tmp19 + tmp24;
			float tmp29 = 0;
			float tmp30 = 0;
			float tmp31 = 0;
			if (0 <= H129 - (1)) {
				tmp31 = l[(((m)) * (H128 + 1)) + H129 - (1)];
			}
			float tmp32 = 0;
			tmp32 = l[(((m)) * (H128 + 1)) + H129];
			tmp30 = tmp31 + tmp32;
			float tmp33 = 0;
			tmp33 = l[(((m)) * (H128 + 1)) + H129 + 1];
			tmp29 = tmp30 + tmp33;
			output[(((1 + ((m - (1 + 0)) - (1 + 0))) + (m - (m - (1))))) * (((H128 - (1)) + 1)) + H129] = tmp18 + tmp29;
		}
	}
#pragma omp parallel for
	for (int H150 = 0; H150 < (((n - (1 + 0)) - (1)) / (64)); H150++) {
		for (int H162 = 0; H162 < ((((m - (1 + 0)) - (1 + 0))) / (64)); H162++) {
			float* tmp34 = (float*) calloc(1,(66) * (64) * sizeof (float));
			for (int H165 = 0; H165 < 66; H165++) {
				for (int H166 = 0; H166 < 64; H166++) {
					float tmp35 = 0;
					float tmp36 = 0;
					tmp36 = l[(((m)) * ((H150) * (64) + H165)) + (H162) * (64) + H166];
					float tmp37 = 0;
					tmp37 = l[(((m)) * ((H150) * (64) + H165)) + (H162) * (64) + H166 + 1];
					tmp35 = tmp36 + tmp37;
					float tmp38 = 0;
					tmp38 = l[(((m)) * ((H150) * (64) + H165)) + (H162) * (64) + H166 + 2];
					tmp34[(64) * (H165) + H166] = tmp35 + tmp38;
				}
			}
			float* x10 = tmp34;
			for (int H168 = 0; H168 < 64; H168++) {
				for (int H169 = 0; H169 < 64; H169++) {
					float tmp39 = 0;
					float tmp40 = 0;
					tmp40 = x10[(((64)) * (H168)) + H169];
					float tmp41 = 0;
					tmp41 = x10[(((64)) * (H168 + 1)) + H169];
					tmp39 = tmp40 + tmp41;
					float tmp42 = 0;
					tmp42 = x10[(((64)) * (H168 + 2)) + H169];
					output[(((1 + ((m - (1 + 0)) - (1 + 0))) + (m - (m - (1))))) * (((H150) * (64) + H168 + 1)) + ((H162) * (64) + H169 + 1)] = tmp39 + tmp42;
				}
			}
			free(tmp34);
		}
		for (int H188 = ((((m - (1 + 0)) - (1 + 0))) / (64)); H188 < ((((m - (1 + 0)) - (1 + 0))) / (64)) + ((((((m - (1 + 0)) - (1 + 0))) % (64))) + (64) - 1 ) / (64); H188++) {
			for (int H189 = 0; H189 < 64; H189++) {
				for (int H190 = 0; H190 < 64; H190++) {
					if ((H188) * (64) + H189 < ((m - (1 + 0)) - (1 + 0))) {
						if ((H150) * (64) + H190 < (n - (1 + 0)) - (1)) {
							float tmp43 = 0;
							float tmp44 = 0;
							float tmp45 = 0;
							float tmp46 = 0;
							tmp46 = l[(((m)) * ((H150) * (64) + H190)) + (H188) * (64) + H189];
							float tmp47 = 0;
							tmp47 = l[(((m)) * ((H150) * (64) + H190)) + (H188) * (64) + H189 + 1];
							tmp45 = tmp46 + tmp47;
							float tmp48 = 0;
							tmp48 = l[(((m)) * ((H150) * (64) + H190)) + (H188) * (64) + H189 + 1 + 1];
							tmp44 = tmp45 + tmp48;
							float tmp49 = 0;
							float tmp50 = 0;
							float tmp51 = 0;
							tmp51 = l[(((m)) * ((H150) * (64) + H190 + 1)) + (H188) * (64) + H189];
							float tmp52 = 0;
							tmp52 = l[(((m)) * ((H150) * (64) + H190 + 1)) + (H188) * (64) + H189 + 1];
							tmp50 = tmp51 + tmp52;
							float tmp53 = 0;
							tmp53 = l[(((m)) * ((H150) * (64) + H190 + 1)) + (H188) * (64) + H189 + 1 + 1];
							tmp49 = tmp50 + tmp53;
							tmp43 = tmp44 + tmp49;
							float tmp54 = 0;
							float tmp55 = 0;
							float tmp56 = 0;
							tmp56 = l[(((m)) * ((H150) * (64) + H190 + 1 + 1)) + (H188) * (64) + H189];
							float tmp57 = 0;
							tmp57 = l[(((m)) * ((H150) * (64) + H190 + 1 + 1)) + (H188) * (64) + H189 + 1];
							tmp55 = tmp56 + tmp57;
							float tmp58 = 0;
							tmp58 = l[(((m)) * ((H150) * (64) + H190 + 1 + 1)) + (H188) * (64) + H189 + 1 + 1];
							tmp54 = tmp55 + tmp58;
							output[(((1 + ((m - (1 + 0)) - (1 + 0))) + (m - (m - (1))))) * (((H150) * (64) + H190 + 1)) + ((((H188 - (((((m - (1 + 0)) - (1 + 0))) / (64)))) + ((((m - (1 + 0)) - (1 + 0))) / (64)))) * (64) + H189 + 1)] = tmp43 + tmp54;
						}
					}
				}
			}
		}
	}
#pragma omp parallel for
	for (int H191 = (((n - (1 + 0)) - (1)) / (64)); H191 < (((n - (1 + 0)) - (1)) / (64)) + (((((n - (1 + 0)) - (1)) % (64))) + (64) - 1 ) / (64); H191++) {
		for (int H192 = 0; H192 < ((((m - (1 + 0)) - (1 + 0))) / (64)) + ((((((m - (1 + 0)) - (1 + 0))) % (64))) + (64) - 1 ) / (64); H192++) {
			for (int H193 = 0; H193 < 64; H193++) {
				for (int H194 = 0; H194 < 64; H194++) {
					if ((H192) * (64) + H193 < ((m - (1 + 0)) - (1 + 0))) {
						if ((H191) * (64) + H194 < (n - (1 + 0)) - (1)) {
							float tmp59 = 0;
							float tmp60 = 0;
							float tmp61 = 0;
							float tmp62 = 0;
							tmp62 = l[(((m)) * ((H191) * (64) + H194)) + (H192) * (64) + H193];
							float tmp63 = 0;
							tmp63 = l[(((m)) * ((H191) * (64) + H194)) + (H192) * (64) + H193 + 1];
							tmp61 = tmp62 + tmp63;
							float tmp64 = 0;
							tmp64 = l[(((m)) * ((H191) * (64) + H194)) + (H192) * (64) + H193 + 1 + 1];
							tmp60 = tmp61 + tmp64;
							float tmp65 = 0;
							float tmp66 = 0;
							float tmp67 = 0;
							tmp67 = l[(((m)) * ((H191) * (64) + H194 + 1)) + (H192) * (64) + H193];
							float tmp68 = 0;
							tmp68 = l[(((m)) * ((H191) * (64) + H194 + 1)) + (H192) * (64) + H193 + 1];
							tmp66 = tmp67 + tmp68;
							float tmp69 = 0;
							tmp69 = l[(((m)) * ((H191) * (64) + H194 + 1)) + (H192) * (64) + H193 + 1 + 1];
							tmp65 = tmp66 + tmp69;
							tmp59 = tmp60 + tmp65;
							float tmp70 = 0;
							float tmp71 = 0;
							float tmp72 = 0;
							tmp72 = l[(((m)) * ((H191) * (64) + H194 + 1 + 1)) + (H192) * (64) + H193];
							float tmp73 = 0;
							tmp73 = l[(((m)) * ((H191) * (64) + H194 + 1 + 1)) + (H192) * (64) + H193 + 1];
							tmp71 = tmp72 + tmp73;
							float tmp74 = 0;
							tmp74 = l[(((m)) * ((H191) * (64) + H194 + 1 + 1)) + (H192) * (64) + H193 + 1 + 1];
							tmp70 = tmp71 + tmp74;
							output[(((1 + ((m - (1 + 0)) - (1 + 0))) + (m - (m - (1))))) * (((((H191 - ((((n - (1 + 0)) - (1)) / (64)))) + (((n - (1 + 0)) - (1)) / (64)))) * (64) + H194 + 1)) + ((H192) * (64) + H193 + 1)] = tmp59 + tmp70;
						}
					}
				}
			}
		}
	}
#pragma omp parallel for
	for (int H195 = 1; H195 < (n - (1 + 0)); H195++) {
		for (int H196 = m - (1); H196 < m; H196++) {
			float tmp75 = 0;
			float tmp76 = 0;
			float tmp77 = 0;
			float tmp78 = 0;
			float tmp79 = 0;
			tmp79 = l[(((m)) * (H195 - (1))) + H196 - (1)];
			float tmp80 = 0;
			tmp80 = l[(((m)) * (H195 - (1))) + H196];
			tmp78 = tmp79 + tmp80;
			float tmp81 = 0;
			if (H196 + 1 < m) {
				tmp81 = l[(((m)) * (H195 - (1))) + H196 + 1];
			}
			tmp77 = tmp78 + tmp81;
			float tmp82 = 0;
			float tmp83 = 0;
			float tmp84 = 0;
			tmp84 = l[(((m)) * (H195)) + H196 - (1)];
			float tmp85 = 0;
			tmp85 = l[(((m)) * (H195)) + H196];
			tmp83 = tmp84 + tmp85;
			float tmp86 = 0;
			if (H196 + 1 < m) {
				tmp86 = l[(((m)) * (H195)) + H196 + 1];
			}
			tmp82 = tmp83 + tmp86;
			tmp76 = tmp77 + tmp82;
			float tmp87 = 0;
			float tmp88 = 0;
			tmp88 = l[(((m)) * (H195 + 1)) + H196 - (1)];
			float tmp89 = 0;
			tmp89 = l[(((m)) * (H195 + 1)) + H196];
			tmp87 = tmp88 + tmp89;
			tmp75 = tmp76 + tmp87;
			float tmp90 = 0;
			if (H196 + 1 < m) {
				tmp90 = l[(((m)) * (H195 + 1)) + H196 + 1];
			}
			output[(((1 + ((m - (1 + 0)) - (1 + 0))) + (m - (m - (1))))) * (((H195 - (1)) + 1)) + ((H196 - (m - (1))) + (1 + ((m - (1 + 0)) - (1 + 0))))] = tmp75 + tmp90;
		}
	}
#pragma omp parallel for
	for (int H197 = n - (1); H197 < n; H197++) {
		for (int H198 = 0; H198 < m; H198++) {
			float tmp91 = 0;
			float tmp92 = 0;
			float tmp93 = 0;
			float tmp94 = 0;
			if (0 <= H198 - (1)) {
				tmp94 = l[(((m)) * (H197 - (1))) + H198 - (1)];
			}
			float tmp95 = 0;
			tmp95 = l[(((m)) * (H197 - (1))) + H198];
			tmp93 = tmp94 + tmp95;
			float tmp96 = 0;
			if (H198 + 1 < m) {
				tmp96 = l[(((m)) * (H197 - (1))) + H198 + 1];
			}
			tmp92 = tmp93 + tmp96;
			float tmp97 = 0;
			float tmp98 = 0;
			float tmp99 = 0;
			if (0 <= H198 - (1)) {
				tmp99 = l[(((m)) * (H197)) + H198 - (1)];
			}
			float tmp100 = 0;
			tmp100 = l[(((m)) * (H197)) + H198];
			tmp98 = tmp99 + tmp100;
			float tmp101 = 0;
			if (H198 + 1 < m) {
				tmp101 = l[(((m)) * (H197)) + H198 + 1];
			}
			tmp97 = tmp98 + tmp101;
			tmp91 = tmp92 + tmp97;
			float tmp102 = 0;
			if (H197 + 1 < n) {
				float tmp103 = 0;
				float tmp104 = 0;
				if (0 <= H198 - (1)) {
					tmp104 = l[(((m)) * (H197 + 1)) + H198 - (1)];
				}
				float tmp105 = 0;
				tmp105 = l[(((m)) * (H197 + 1)) + H198];
				tmp103 = tmp104 + tmp105;
				float tmp106 = 0;
				if (H198 + 1 < m) {
					tmp106 = l[(((m)) * (H197 + 1)) + H198 + 1];
				}
				tmp102 = tmp103 + tmp106;
			}
			output[(m) * (((H197 - (n - (1))) + (1 + ((n - (1 + 0)) - (1))))) + H198] = tmp91 + tmp102;
		}
	}
}

