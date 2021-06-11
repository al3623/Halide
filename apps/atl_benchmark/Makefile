immediate_run: immediate_run.cpp blur_immediate.a
	g++ immediate_run.cpp blur_immediate.a -g -std=c++11 -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_run

blur_immediate.a: immediate_generate
	./immediate_generate

immediate_generate:
	g++ immediate_generate.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_generate

.PHONY: clean

clean:
	rm immediate_run immediate_generate *.a *.h
