CC := clang
CCPP := clang++
STEMS	:= $(wildcard blur*.cpp)
LIBS := $(patsubst %.cpp,%.a, $(STEMS))
GENS := $(patsubst %.cpp,%.gen, $(STEMS))
HL_INSTALL := /Users/gilbo/code/Halide-coq-atl/install
HL_INC := $(HL_INSTALL)/include
HL_TOOLS := $(HL_INSTALL)/share/tools
HL_LIB := $(HL_INSTALL)/lib


ATL_STEMS := $(wildcard atl/*.c)
ATL_OBJECTS := $(patsubst %.c,%.o, $(ATL_STEMS))

run: atl run.cpp $(LIBS) 
	$(CCPP) run.cpp atl/libscheds.a $(LIBS) -g -std=c++17 -arch x86_64 \
	      -Wl,-rpath $(HL_LIB) \
	      -I $(HL_INC) -I atl/ -I $(HL_TOOLS) \
	      -L $(HL_LIB) -lHalide -lpthread -ldl \
	      -o run

profile: atl run.cpp $(LIBS) 
	$(CCPP) run.cpp atl/libscheds.a $(LIBS) -g -std=c++17 -arch x86_64 \
	      -Wl,-rpath $(HL_LIB) \
	      -I $(HL_INC) -I atl/ -I $(HL_TOOLS) \
	      -L $(HL_LIB) -lHalide -lpthread -ldl \
	      -pg -o profile

%.a: %.gen
	./$^

%.gen: %.cpp
	$(CCPP) $^ -g -std=c++17 -arch x86_64 \
	      -Wl,-rpath $(HL_LIB) \
	      -I $(HL_INC) \
	      -L $(HL_LIB) -lHalide -lpthread -ldl \
	      -o $@

.PHONY: clean atl
.SECONDARY: $(GENS)

atl: atl/libscheds.a

atl/libscheds.a: $(ATL_OBJECTS)
	ar rc $@ $^ 
	ranlib $@

atl/%.o: atl/%.c
	$(CC) -g -arch x86_64 -Wall -ffast-math -O3 -c $^ -o $@

atlclean:
	rm -f atl/*.o atl/*.a atl/*.BAK

clean:
	rm -f *.a *.h *.c *.s *.gen
