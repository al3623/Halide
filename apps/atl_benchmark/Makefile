run: atl run.cpp blur_two_stage_float.a blur_tiled_float.a blur_immediate_float.a
	g++ run.cpp atl/libscheds.a blur_immediate_float.a blur_two_stage_float.a  blur_tiled_float.a -g -std=c++11 -I ../../src/ -I atl/ -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -o run

profile: atl run.cpp blur_two_stage_float.a blur_tiled_float.a blur_immediate_float.a
	g++ run.cpp atl/libscheds.a blur_immediate_float.a blur_two_stage_float.a blur_tiled_float.a -g -std=c++11 -I ../../src/ -I atl/ -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -pg -o profile

blur_immediate_float.a: immediate_generate_float
	./immediate_generate_float

blur_two_stage_float.a: two_stage_generate_float
	./two_stage_generate_float

blur_tiled_float.a: tiled_generate_float
	./tiled_generate_float

immediate_generate_float: immediate_generate_float.cpp
	g++ immediate_generate_float.cpp -g -std=c++11 -I ~/halide_build/include -I ../../src/ -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_generate_float

two_stage_generate_float: two_stage_generate_float.cpp
	g++ two_stage_generate_float.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o two_stage_generate_float

tiled_generate_float: tiled_generate_float.cpp
	g++ tiled_generate_float.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o tiled_generate_float

.PHONY: clean atl

atl:
	make -C atl

clean:
	rm -f run immediate_generate *.a *.h two_stage_generate tiled_generate
