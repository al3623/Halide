#include "Halide.h"
#include <stdio.h>
using namespace Halide;

int main(int argc, char **argv) {

	ImageParam image(type_of<float>(), 2);
    Func blur_x("blur_x");
	Func blur_y("blur_y");
    Var x("x"), y("y");

	Func input = BoundaryConditions::constant_exterior(image,0);

	blur_x(x, y) = (input(x-1, y) + input(x, y) + input(x + 1, y));
	
	blur_y(x, y) = (blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1));
	
	blur_x.compute_root();

    blur_y.compile_to_static_library("blur_two_stage_float", {image}, "two_stage_float");
	blur_y.compile_to_assembly("blur_two_stage_float.s", {image}, "two_stage_float");
    blur_y.print_loop_nest();
    blur_y.compile_to_c("blur_two_stage_float.c", {image}, "two_stage_float");

    printf("Halide pipeline compiled, but not yet run.\n");

    return 0;
}
