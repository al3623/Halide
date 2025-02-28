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
	Expr clamped_x = clamp(x,0,input.width()-1);
	Expr clamped_y = clamp(y,0,input.height()-1);
	Expr guard_x = select(0 <= x && x < input.width(),clamped_x,0);
	Expr guard_y = select(0 <= y && y < input.height(),clamped_y,0);
	Func guarded("guarded");
	guarded(x,y) = input(guard_x, guard_y);

	blur_x(x, y) = (guarded(x-1, y) + guarded(x, y) + guarded(x + 1, y));
	blur_y(x, y) = (blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y + 1));
	blur_y.compile_jit();
	double min_time = Tools::benchmark([&]() {
	              blur_y.realize({input.width(), input.height()}); });
				  printf("\t%d * %d\n",input.height(),input.width());
		          printf("\tBenchmarked runtime (JIT): %gs\n", 
								  min_time);
   // Buffer<uint16_t> output = blur_y.realize({input.width(), input.height()});

    // blur_y.print_loop_nest();
	blur_y.compile_to_c("immediate.c", blur_y.infer_arguments());
	blur_y.compile_to_header("immediate.h", blur_y.infer_arguments());
    //convert_and_save_image(output, "/home/amangoliu/Halide/tutorial/images/blurred_gray.png");
    return 0;
}
