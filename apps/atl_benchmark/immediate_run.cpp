// Halide tutorial lesson 11: AOT compilation part 2

// Before reading this file, see lesson_10_aot_compilation_generate.cpp

// This is the code that actually uses the Halide pipeline we've
// compiled. It does not depend on libHalide, so we won't be including
// Halide.h.
//
// Instead, it depends on the header file that lesson_10_generate
// produced when we ran it:
#include "blur_immediate.h"
#include "blur_two_stage.h"
#include "blur_tiled.h"

#include "blurim.h"
#include "blurtwo.h"
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
	int M = 1000;
	int N = 1000;
	int error = 0;
	int trials = 30;
    // The ImageParam inputs have become pointers to "halide_buffer_t"
    // structs. This is struct that Halide uses to represent arrays of
    // data.  Unless you're calling the Halide pipeline from pure C
    // code, you don't want to use it
    // directly. Halide::Runtime::Buffer is a simple wrapper around
    // halide_buffer_t that will implicitly convert to a
    // halide_buffer_t *. We will pass Halide::Runtime::Buffer objects
    // in those slots.

    // The Halide::Buffer class we have been using in JIT code is in
    // fact just a shared pointer to the simpler
    // Halide::Runtime::Buffer class. They share the same API.

	Halide::Runtime::Buffer<uint8_t> input(M, N)
			, output1(M, N)
			, output2(M, N)
			, output3(M, N);

	halide_buffer_t ptr = input.get_buf();
	uint8_t *v = ptr.host;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			input(x,y) = (uint8_t) rand();
			// (uint8_t) (x+y);
        }
    }
 
	error = 0;
	double t = Halide::Tools::benchmark(trials,1,[&]() { 
    	error = immediate(input, output1);
		});

    if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("immediate\t%d\t%d\t%gms\n",N,M,t*1000);
	}

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
			uint8_t out1 = output1(x,y);
			uint8_t out2 = output2(x,y);
			uint8_t out3 = output3(x,y);
			if (out1 != out2) {
				printf("Ohno im two :(\n");
			}
			if (out3 != out2) {
				printf("Ohno tile two :(\n");
			}
        }
   }

   // ATL benchmarks
   u_int8_t *res1 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurim(v,M,N,res1);
		});
   printf("blurim atl \t%d\t%d\t%gms\n",N,M,t*1000);

   u_int8_t *res2 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtwo(v,M,N,res2);
		});
   printf("two stage atl \t%d\t%d\t%gms\n",N,M,t*1000);

   u_int8_t *res3 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(trials,1,[&]() { 
    	blurtiles(v,M,N,res3);
		});
   printf("tiled 4 atl \t%d\t%d\t%gms\n",N,M,t*1000);

   for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
			int i = y * M + x;
			uint8_t out1 = res1[i];
			uint8_t out2 = res2[i];
			uint8_t out3 = res3[i];
			if (out1 != out2) {
				printf("Ohno atl :(\n");
			}
			if (out3 != out2) {
				printf("Ohno atl :(\n");
			}
        }
   }
 
   for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int i = y * M + x;
			uint8_t atlout = res1[i];
			uint8_t halideout = output1(x,y);
			if (atlout != halideout) {
				printf("(%d,%d): %d!=%d\n",x,y,atlout,halideout);
			}
       }
   }
 
   free(res1);
   free(res2);
   free(res3);

   return 0;
}
