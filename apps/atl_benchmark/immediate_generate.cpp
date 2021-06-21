#include "Halide.h"
#include <stdio.h>
using namespace Halide;

int main(int argc, char **argv) {

	ImageParam image(type_of<uint8_t>(), 2);

    Func blur_x("blur_x");
	Func blur_y("blur_y");
    Var x("x"), y("y");

	/*	
	Func clamped("clamped");
	clamped(x,y) = image(clamp(x,0,image.width()-1),clamp(y,0,image.height()-1));

	Func guardx("guardx");
	guardx(x,y) = select(0 <= x && x < image.width()
					, clamped(x,y)
					, 0);

	blur_x(x, y) = (guardx(x-1, y) + guardx(x, y) + guardx(x +1, y));

	Func guardy("guardy");
	guardy(x,y) = select(0 <= y && y < image.height()
					, blur_x(x,y)
					, 0);
	blur_y(x, y) = guardy(x, y-1) + guardy(x, y) + guardy(x, y + 1);
	*/
	/*
	Func clamped("clamped");
	clamped(x,y) = image(clamp(x,0,image.width()-1),clamp(y,0,image.height()-1));

	blur_x(x, y) = (clamped(x-1, y) + clamped(x, y) + clamped(x +1, y));
	blur_y(x, y) = blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1);
	*/
		
	Func input("input");
	input = BoundaryConditions::constant_exterior(image,0);

	blur_x(x,y) = input(x-1,y) + input(x,y) + input(x+1,y);
	blur_y(x,y) = blur_x(x,y-1) + blur_x(x,y) + blur_x(x,y+1);
	
	/*
	Func clamped("clamped");
	clamped(x,y) = image(clamp(x,0,image.width()-1),clamp(y,0,image.height()-1));

	Func guard("guard");
	guard(x,y) = select(0 <= x && x < image.width() 
					&& 0 <= y && y < image.height()
					, clamped(x,y)
					, 0);

	blur_x(x, y) = (guard(x-1, y) + guard(x, y) + guard(x +1, y));

	blur_y(x, y) = blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1);
	*/
    blur_y.compile_to_static_library("blur_immediate", {image}, "immediate");
    blur_y.compile_to_c("blur_immediate.c", {image}, "immediate");
	blur_y.print_loop_nest();

    printf("Halide pipeline compiled, but not yet run.\n");

    return 0;
}
