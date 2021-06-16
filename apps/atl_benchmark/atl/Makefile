CC = g++
CFLAGS = -g -Wall
LDFLAGS = -g

GENFILE := gen
STEMS	:= $(wildcard *.c)
OBJECTS := $(patsubst %.c,%.o, $(STEMS))

libscheds.a: $(OBJECTS)
	ar rc $@ $^ 
	ranlib $@

%.o: %.c
	$(CC) -g -Wall -ffast-math -O3 -c $^ -o $@

.PHONY: clean scrub

scrub: 
	./cleanoutput.sh $(GENFILE)

clean:
	rm -f *.o a.out core main *.a $(GENFILE)
