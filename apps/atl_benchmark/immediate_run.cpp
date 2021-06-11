// Halide tutorial lesson 10: AOT compilation part 2

// Before reading this file, see lesson_10_aot_compilation_generate.cpp

// This is the code that actually uses the Halide pipeline we've
// compiled. It does not depend on libHalide, so we won't be including
// Halide.h.
//
// Instead, it depends on the header file that lesson_10_generate
// produced when we ran it:
#include "blur_immediate.h"

// We want to continue to use our Halide::Buffer with AOT-compiled
// code, so we explicitly include it. It's a header-only class, and
// doesn't require libHalide.
#include "HalideBuffer.h"

#include <stdio.h>

int main(int argc, char **argv) {
    // Have a look in the header file above (it won't exist until you've run
    // lesson_10_generate). At the bottom is the signature of the function we generated:

    // int brighter(halide_buffer_t *_input_buffer, uint8_t _offset, halide_buffer_t *_brighter_buffer);

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

    // Finally, the return value of "brighter" is an error code. It's
    // zero on success.

    // Let's make a buffer for our input and output.
    Halide::Runtime::Buffer<uint8_t> input(640, 480), output(640, 480);
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
			input(x,y) = (uint8_t) rand();
           }
        }

    int error = immediate(input, output);

    if (error) {
        printf("Halide returned an error: %d\n", error);
        return -1;
    }

    // Now let's check the filter performed as advertised. It was
    // supposed to add the offset to every input pixel.
    // Everything worked!
    printf("Success!\n");
    return 0;
}
