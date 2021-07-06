
CC := clang
CXX := clang++

LDFLAGS += $(shell $(LLVM_CONFIG) --ldflags)
CFLAGS += $(shell $(LLVM_CONFIG) --cflags)
CXXFLAGS += $(shell $(LLVM_CONFIG) --cxxflags)

ifeq ($(OS),Windows_NT)
  echo windows
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Darwin)
    ADD_SYS_LLVM := --sysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
    CFLAGS += $(ADD_SYS_LLVM)
    CXXFLAGS += $(ADD_SYS_LLVM)
    CXXFLAGS += -I /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1
  endif
endif

STEMS	:= $(wildcard blur*.cpp)
LIBS := $(patsubst %.cpp,%.a, $(STEMS))
GENS := $(patsubst %.cpp,%.gen, $(STEMS))
HL_INSTALL := /home/amangoliu/halide_build/distrib
HL_INC := $(HL_INSTALL)/include
HL_TOOLS := $(HL_INSTALL)/tools
HL_LIB := $(HL_INSTALL)/lib



ATL_STEMS := $(wildcard atl/*.c)
ATL_OBJECTS := $(patsubst %.c,%.o, $(ATL_STEMS))

run: atl run.cpp $(LIBS) 
	$(CXX) run.cpp atl/libscheds.a $(LIBS) -g $(CXXFLAGS) $(LDFLAGS) \
	      -std=c++17  \
	      -fopenmp \
	      -Wl,-rpath $(HL_LIB) \
	      -I $(HL_INC) -I atl/ -I $(HL_TOOLS) \
	      -L $(HL_LIB) -lHalide -lpthread -ldl \
	      -o run

profile: atl run.cpp $(LIBS) 
	$(CXX) run.cpp atl/libscheds.a $(LIBS) -g $(CXXFLAGS) $(LDFLAGS) \
	      -std=c++17  \
	      -Wl,-rpath $(HL_LIB) \
	      -I $(HL_INC) -I atl/ -I $(HL_TOOLS) \
	      -L $(HL_LIB) -lHalide -lpthread -ldl \
	      -pg -o profile

%.a: %.gen
	./$^

%.gen: %.cpp
	$(CXX) $^ -g $(CXXFLAGS) \
	      -std=c++17 \
	      -Wl,-rpath $(HL_LIB) \
	      -I $(HL_INC) \
	      -L $(HL_LIB) -lHalide -lpthread -ldl \
	      -o $@

.PHONY: clean atl atlclean
.SECONDARY: $(GENS)

atl: atl/libscheds.a

atl/libscheds.a: $(ATL_OBJECTS)
	ar rc $@ $^ 
	ranlib $@

atl/%.o: atl/%.c
	$(CC) -g $(CFLAGS)  -std=c11 -Wall \
	-fopenmp \
	-ffast-math -O3 \
	-c $^ -o $@

atlclean:
	rm -f atl/*.o atl/*.a atl/*.BAK

clean:
	rm -f *.a *.h *.c *.s *.gen
	rm -rf *.dSYM
