run: atl run.cpp blur_immediate.a blur_two_stage.a blur_tiled.a blur_immediate_sc.a
	g++ run.cpp atl/libscheds.a blur_immediate.a blur_immediate_sc.a blur_two_stage.a blur_tiled.a -g -std=c++11 -I ../../src/ -I atl/ -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -o run

blur_immediate.a: immediate_generate
	./immediate_generate

blur_immediate_sc.a: immediate_generate_sc
	./immediate_generate_sc

blur_two_stage.a: two_stage_generate
	./two_stage_generate

blur_tiled.a: tiled_generate
	./tiled_generate

immediate_generate: immediate_generate.cpp
	g++ immediate_generate.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_generate

immediate_generate_sc: immediate_generate_sc.cpp
	g++ immediate_generate_sc.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o immediate_generate_sc

two_stage_generate: two_stage_generate.cpp
	g++ two_stage_generate.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o two_stage_generate

tiled_generate: tiled_generate.cpp
	g++ tiled_generate.cpp -g -std=c++11 -I ~/halide_build/include -L ~/halide_build/bin -lHalide -lpthread -ldl -o tiled_generate

.PHONY: clean atl

atl:
	make -C atl

clean:
	rm -f run immediate_generate *.a *.h two_stage_generate tiled_generate
