// Halide tutorial lesson 11: AOT compilation part 2

// Before reading this file, see lesson_10_aot_compilation_generate.cpp

// This is the code that actually uses the Halide pipeline we've
// compiled. It does not depend on libHalide, so we won't be including
// Halide.h.
//
// Instead, it depends on the header file that lesson_10_generate
// produced when we ran it:
#include "blur_immediate_float.h"
#include "blur_two_stage_float.h"
#include "blur_tiled_float.h"

extern "C" {
	#include "blurpart.h"
	#include "blurtwopart.h"
	#include "blurtiles.h"
};

// We want to continue to use our Halide::Buffer with AOT-compiled
// code, so we explicitly include it. It's a header-only class, and
// doesn't require libHalide.
#include "HalideBuffer.h"
#include "IntrusivePtr.h"
#include "halide_benchmark.h"
#include "runtime/HalideBuffer.h"

#include <stdio.h>

int main(int argc, char **argv) {
	int M = 2000;
	int N = 2000;
	int error = 0;
	int trials = 30;
	double t = 0; 

	Halide::Runtime::Buffer<float> input(M, N)
			, output1(M, N)
			, output2(M, N)
			, output3(M,N);

	for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			input(x,y) = (random() % 10);
        }
    }
 
	halide_buffer_t ptrf = input.get_buf();
	float *vf = (float *) ptrf.host;

	error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = immediate_float(input, output1);
		});

    if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("immediate f\t%d\t%d\t%gms\n",N,M,t*1000);
	}

 	float *res2 = (float *) calloc(1,N*M* sizeof (float));
 	t = Halide::Tools::benchmark(1,1,[&]() { 
    	blurpart(vf,M,N,res2);
		});
    printf("immediate atl f\t%d\t%d\t%gms\n",N,M,t*1000);
 

	error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = two_stage_float(input, output3);
		});
	
	if (error) {
    	printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("two_stage f\t%d\t%d\t%gms\n", N,M,t*1000);
	}

	float *res3 = (float *) calloc(1,N*M* sizeof (float));
    t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtwopart(vf,M,N,res3);
		});
   	printf("two stage atlf\t%d\t%d\t%gms\n",N,M,t*1000);

   error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = tiled_float(input, output2);
		});
   if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("tiled_4 f\t%d\t%d\t%gms\n", N,M,t*1000);
	}

   float *res1 = (float *) calloc(1,N*M* sizeof (float));
   t = Halide::Tools::benchmark(1,1,[&]() { 
    	blurtiles(vf,M,N,res1);
		});
   printf("tiled 4 atl f \t%d\t%d\t%gms\n",N,M,t*1000);

   float* loutput = (float*) malloc((N) * (M) * sizeof (float));
	float* routput = (float*) malloc((N) * (M) * sizeof (float));

	blurpart(vf,M,N,loutput);
	blurtiles(vf,M,N,routput);
	for (int H4 = 0; H4 < (N) * (M); H4++) {
		if (routput[H4] != loutput[H4]) {
				printf("neq norm\n");
		}
	}

 	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int i = y * M + x;
			float atlout1 = res1[i];
			float atlout2 = res2[i];
			float atlout3 = res3[i];
			float halideoutf = output1(x,y);
			float halidetwof = output3(x,y);
			float halidetilef = output2(x,y);
/*
			if (atlout2 != atlout1) {
				printf("Neq tile im: %f %f\n", atlout2, atlout1);
				goto out;
			}
			*/
			if (atlout2 != atlout3) {
				printf("Neq f\n");
				goto out;
			}
			if (halidetwof != halidetilef) {
				printf("Neq f\n");
				goto out;
			}
			if (halidetwof != halideoutf) {
				printf("Neq f\n");
				goto out;
			}
			if (atlout2 != halideoutf) {
				printf("Neq f\n");
				goto out;
			}
			if (atlout3 != halidetwof) {
				printf("Neq f\n");
				goto out;
			}
			if (atlout1 != halidetilef) {
				printf("Neq tile: %f %f\n", atlout1, halidetilef);
				goto out;
			}
	
       }
   }

out:

   return 0;
}
