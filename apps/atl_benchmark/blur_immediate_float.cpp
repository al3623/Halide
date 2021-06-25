#include "Halide.h"
#include "Pipeline.h"
#include <stdio.h>
using namespace Halide;

int main(int argc, char **argv) {

	ImageParam image(type_of<float>(), 2);

    Func blur_x("blur_x");
	Func blur_y("blur_y");
    Var x("x"), y("y");
		
	Func input("input");
	input = BoundaryConditions::constant_exterior(image,0);

	blur_x(x,y) = input(x-1,y) + input(x,y) + input(x+1,y);
	blur_y(x,y) = blur_x(x,y-1) + blur_x(x,y) + blur_x(x,y+1);
	
	// blur_y.vectorize(x,32);
    blur_y.compile_to_static_library("blur_immediate_float", {image}, "immediate_float");
	blur_y.compile_to_assembly("blur_immediate_float.s", {image}, "immediate_float");

    blur_y.compile_to_c("blur_immediate_float.c", {image}, "immediate_float");
	blur_y.print_loop_nest();

    printf("Halide pipeline compiled, but not yet run.\n");

    return 0;
}
