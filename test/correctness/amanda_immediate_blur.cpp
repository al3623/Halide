#include "Halide.h"
// Include some support code for loading pngs.
#include "halide_image_io.h"
#include "halide_benchmark.h"
using namespace Halide::Tools;
using namespace Halide;
int main(void) {
    Buffer<uint16_t> input = 
			load_and_convert_image(
							"/home/amangoliu/Halide/tutorial/images/gray.png");
    Func blur_x("blur_x");
	Func blur_y("blur_y");
    Var x("x"), y("y"), xi("xi"), yi("yi"), xo("xo"), yo("yo");
	// The algorithm
	Expr clamped_x = clamp(x,1,input.width()-1);
	Expr clamped_y = clamp(x,1,input.height()-1);
	Func clamped("clamped");
	clamped(x,y) = input(clamped_x, clamped_y);

	blur_x(x, y) = (clamped(x-1, y) + clamped(x, y) + clamped(x + 1, y)) / 3;
	blur_y(x, y) = (blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1)) / 3;
	blur_y.compile_jit();
	double min_time = Tools::benchmark([&]() {
	              blur_y.realize({input.width(), input.height()}); });
				  printf("\t%d * %d\n",input.height(),input.width());
		          printf("\tBenchmarked runtime (JIT): %gms\n", 
								  min_time * 1e3);
   // Buffer<uint16_t> output = blur_y.realize({input.width(), input.height()});

    blur_y.print_loop_nest();
	blur_y.compile_to_c("immediate.c", blur_y.infer_arguments());
    //convert_and_save_image(output, "/home/amangoliu/Halide/tutorial/images/blurred_gray.png");
    return 0;
}
