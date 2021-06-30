CC := clang++
STEMS	:= $(wildcard blur*.cpp)
LIBS := $(patsubst %.cpp,%.a, $(STEMS))

run: atl run.cpp $(LIBS) 
	$(CC) run.cpp atl/libscheds.a $(LIBS) -g -std=c++11 -I ../../src/ -I atl/ -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -o run

profile: atl run.cpp $(LIBS) 
	$(CC) run.cpp atl/libscheds.a $(LIBS) -g -std=c++11 -I ../../src/ -I atl/ -I ~/halide_build/include -I ~/halide_build/distrib/tools -L ~/halide_build/bin -lHalide -lpthread -ldl -pg -o profile

%.a: %.gen
	./$^

%.gen: %.cpp
	$(CC) $^ -g -std=c++11 -I ~/halide_build/include -I ../../src/ -L ~/halide_build/bin -lHalide -lpthread -ldl -o $@

.PHONY: clean atl

atl:
	make -C atl

clean:
	rm -f *.a *.h *.c *.s
