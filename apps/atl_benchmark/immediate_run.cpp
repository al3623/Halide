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
	int M = 2000;
	int N = 2000;
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
           }
        }

	int error = 0;
	double t = Halide::Tools::benchmark(10,1,[&]() { 
    	error = immediate(input, output1);
		});

    if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("immediate\t%gs\n", t);
	}

	error = 0;
	t = Halide::Tools::benchmark(10,1,[&]() { 
    	error = two_stage(input, output2);
		});
	
   if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("two_stage\t%gs\n", t);
	}

	error = 0;
	t = Halide::Tools::benchmark(10,1,[&]() { 
    	error = tiled(input, output3);
		});
	
   if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    } else {
		printf("tiled_4 \t%gs\n", t);
	}

   // ATL benchmarks
   u_int8_t *res1 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(10,1,[&]() { 
    	blurim(v,M,N,res1);
		});
   free(res1);
   printf("blurim atl \t%gs\n",t);

   u_int8_t *res2 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(10,1,[&]() { 
    	blurtwo(v,M,N,res2);
		});
   free(res2);
   printf("two stage atl \t%gs\n",t);

   u_int8_t *res3 = (u_int8_t *) calloc(1,N*M* sizeof (u_int8_t));
   t = Halide::Tools::benchmark(10,1,[&]() { 
    	blurtiles(v,M,N,res3);
		});
   free(res3);
   printf("tiled 4 atl \t%gs\n",t);


   return 0;
}
