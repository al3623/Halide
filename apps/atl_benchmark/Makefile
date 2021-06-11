immediate_run: immediate_run.cpp blur_immediate.a blur_two_stage.a
	g++ immediate_run.cpp blur_immediate.a blur_two_stage.a -g -std=c++11 -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_run

blur_immediate.a: immediate_generate
	./immediate_generate

blur_two_stage.a: two_stage_generate
	./two_stage_generate

immediate_generate:
	g++ immediate_generate.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_generate

two_stage_generate:
	g++ two_stage_generate.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o two_stage_generate

.PHONY: clean

clean:
	rm immediate_run immediate_generate *.a *.h two_stage_generate 
