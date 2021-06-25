// Halide tutorial lesson 10: AOT compilation part 1

// This lesson demonstrates how to use Halide as an more traditional
// ahead-of-time (AOT) compiler.

// This lesson is split across two files. The first (this one), builds
// a Halide pipeline and compiles it to a static library and
// header. The second (lesson_10_aot_compilation_run.cpp), uses that
// static library to actually run the pipeline. This means that
// compiling this code is a multi-step process.

// On linux, you can compile and run it like so:
// g++ lesson_10*generate.cpp -g -std=c++11 -I <path/to/Halide.h> -L <path/to/libHalide.so> -lHalide -lpthread -ldl -o lesson_10_generate
// LD_LIBRARY_PATH=<path/to/libHalide.so> ./lesson_10_generate
// g++ lesson_10*run.cpp lesson_10_halide.a -std=c++11 -I <path/to/Halide.h> -lpthread -ldl -o lesson_10_run
// ./lesson_10_run

// On os x:
// g++ lesson_10*generate.cpp -g -std=c++11 -I <path/to/Halide.h> -L <path/to/libHalide.so> -lHalide -o lesson_10_generate
// DYLD_LIBRARY_PATH=<path/to/libHalide.dylib> ./lesson_10_generate
// g++ lesson_10*run.cpp lesson_10_halide.a -o lesson_10_run -I <path/to/Halide.h>
// ./lesson_10_run

// The benefits of this approach are that the final program:
// - Doesn't do any jit compilation at runtime, so it's fast.
// - Doesn't depend on libHalide at all, so it's a small, easy-to-deploy binary.

// If you have the entire Halide source tree, you can also build it by
// running:
//    make tutorial_lesson_10_aot_compilation_run
// in a shell with the current directory at the top of the halide
// source tree.

#include "Halide.h"
#include <stdio.h>
using namespace Halide;

int main(int argc, char **argv) {

	ImageParam image(type_of<uint8_t>(), 2);
    Func blur_x("blur_x");
	Func blur_y("blur_y");
    Var x("x"), y("y");

	Func input = BoundaryConditions::constant_exterior(image,0);

	blur_x(x, y) = (input(x-1, y) + input(x, y) + input(x + 1, y));
	
	blur_y(x, y) = (blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1));
	
	blur_x.compute_root();

    blur_y.compile_to_static_library("blur_two_stage", {image}, "two_stage");
	blur_y.compile_to_assembly("blur_two_stage.s", {image}, "immediate_float");
    blur_y.print_loop_nest();
    blur_y.compile_to_c("blur_two_stage.c", {image}, "two_stage");

    printf("Halide pipeline compiled, but not yet run.\n");

    return 0;
}
