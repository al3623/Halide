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

#include "blurpartf.h"
#include "blurtwopartf.h"
#include "blurtilesf.h"

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

	Halide::Runtime::Buffer<float> inputf(M, N)
			, outputf(M, N)
			, outputf2(M, N)
			, outputf1(M,N);

	halide_buffer_t ptrf = inputf.get_buf();
	float *vf = (float *) ptrf.host;

	for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			inputf(x,y) = (float) (random() % 10);
        }
    }
 
	error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = immediate_float(inputf, outputf);
		});

    if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("immediate f\t%d\t%d\t%gms\n",N,M,t*1000);
	}

 	float *resf = (float *) calloc(1,N*M* sizeof (float));
 	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurpartf(vf,M,N,resf);
		});
    printf("immediate atl f\t%d\t%d\t%gms\n",N,M,t*1000);
 

	error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = two_stage_float(inputf, outputf1);
		});
	
	if (error) {
    	printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("two_stage f\t%d\t%d\t%gms\n", N,M,t*1000);
	}

	float *res6 = (float *) calloc(1,N*M* sizeof (float));
    t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtwopartf(vf,M,N,res6);
		});
   	printf("two stage atlf\t%d\t%d\t%gms\n",N,M,t*1000);

   error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = tiled_float(inputf, outputf2);
		});
   if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("tiled_4 f\t%d\t%d\t%gms\n", N,M,t*1000);
	}

   float *res1 = (float *) calloc(1,N*M* sizeof (float));
   t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtilesf(vf,M,N,res1);
		});
   printf("tiled 4 atl f \t%d\t%d\t%gms\n",N,M,t*1000);



   // Halide is equivalent
   for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
        }
   }
 
   for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			int i = y * M + x;
			float out3f = resf[i];
			float out6f = res6[i];
        }
   }
 
   for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int i = y * M + x;
			float atloutf = resf[i];
			float atloutf1 = res1[i];
			float halideoutf = outputf(x,y);
			float halidetwof = outputf1(x,y);
			float halidetilef = outputf2(x,y);
			float atltwof = res6[i];
			if (atloutf != halideoutf) {
				printf("Neq f\n");
				goto out;
			}
			if (atltwof != halidetwof) {
				printf("Neq f\n");
				goto out;
			}
			if (atloutf1 != halidetilef) {
				printf("Neq f\n");
				goto out;
			}
	
       }
   }

out:

   return 0;
}
