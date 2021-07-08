#include "Halide.h"
#include <stdio.h>
using namespace Halide;

int main(int argc, char **argv) {

	ImageParam image(type_of<float>(), 2);
    Func blur_x("blur_x");
	Func blur_y("blur_y");
    Var x("x"), y("y"), xi("xi"), yi("yi"), xo("xo"), yo("yo");


	Func input = BoundaryConditions::constant_exterior(image,0);
	// The algorithm
	blur_x(x, y) = (input(x-1, y) + input(x, y) + input(x + 1, y));
	blur_y(x, y) = (blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1));

	blur_y.tile(x, y, xo, yo, xi, yi, 64, 64,TailStrategy::GuardWithIf);
    blur_x.compute_at(blur_y, xo);

	blur_y.parallel(yo);	
    blur_y.compile_to_static_library("blur_tiled_float_guard", {image}, "tiled_float_guard");
    blur_y.compile_to_c("blur_tiled_float_guard.c", {image}, "tiled_float_guard");
	blur_y.print_loop_nest();
	blur_y.compile_to_assembly("blur_tiled_float_guard.s", {image}, "tiled_float_guard");

    printf("Halide pipeline compiled, but not yet run.\n");

    // To continue this lesson, look in the file lesson_10_aot_compilation_run.cpp

    return 0;
}
