// Halide tutorial lesson 11: AOT compilation part 2

// Before reading this file, see lesson_10_aot_compilation_generate.cpp

// This is the code that actually uses the Halide pipeline we've
// compiled. It does not depend on libHalide, so we won't be including
// Halide.h.
//
// Instead, it depends on the header file that lesson_10_generate
// produced when we ran it:
#include "blur_immediate_float.h"
#include "blur_two_stage.h"
#include "blur_tiled.h"

#include "blurpartf.h"
#include "blurtwopart.h"
#include "blurtiles.h"

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

	Halide::Runtime::Buffer<uint8_t> input(M, N)
			, output2(M, N)
			, output3(M, N);

	Halide::Runtime::Buffer<float> inputf(M, N)
			, outputf(M, N);

	halide_buffer_t ptr = input.get_buf();
	uint8_t *v = ptr.host;

	halide_buffer_t ptrf = inputf.get_buf();
	float *vf = (float *) ptrf.host;


    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			input(x,y) = (uint8_t) rand();
			// (uint8_t) (x+y);
        }
    }
 
	for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			inputf(x,y) = (float) rand();
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
    	error = two_stage(input, output2);
		});
	
	if (error) {
    	printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("two_stage\t%d\t%d\t%gms\n", N,M,t*1000);
	}

	u_int8_t *res5 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
    t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtwopart(v,M,N,res5);
		});
   	printf("two stage atl\t%d\t%d\t%gms\n",N,M,t*1000);

	error = 0;
	t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = tiled(input, output3);
		});
	
   if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("tiled_4 \t%d\t%d\t%gms\n", N,M,t*1000);
	}

   // Halide is equivalent
   for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			uint8_t out2 = output2(x,y);
			uint8_t out3 = output3(x,y);
			if (out3 != out2) {
				printf("Ohno tile two :(\n");
			}
        }
   }
   
   u_int8_t *res3 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtiles(v,M,N,res3);
		});
   printf("tiled 4 atl \t%d\t%d\t%gms\n",N,M,t*1000);

   for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			int i = y * M + x;
			uint8_t out3 = res3[i];
			uint8_t out5 = res5[i];
 			if (out5 != out3) {
				printf("Ohno atl :(\n");
			}
        }
   }
 
   for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int i = y * M + x;
			uint8_t atlout = res3[i];
			uint8_t halideout = output2(x,y);
			if (atlout != halideout) {
				printf("Neq\n");
				goto out;
			}
       }
   }

out:
 
   free(res3);
   free(res5);

   return 0;
}
