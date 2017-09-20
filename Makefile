# makefile for sample cpputest

CPPUTEST_HOME = c:/cygwin/home/bveenema/cpputest-3.8

CC      := gcc
CFLAGS    := -g -Wall
CFLAGS  += -std=c99
CFLAGS  += -D CPPUTEST            # Compile the test file, ignore the main function of sample.c, the sample.c code with the CPPUTEST macro

# CPPUTest is C++Write, so using g++ To compile the test file
CPP     := g++
CPPFLAGS  := -g -Wall
CPPFLAGS  += -I$(CPPUTEST_HOME)/include

LDFLAGS := -L$(CPPUTEST_HOME)/cpputest_build/lib -lCppUTest

OBJECTS = sample.o test.o


sample: sample.o

sample.o:

# Additional compiled test program
test: $(OBJECTS)
	$(CPP) -o test/$@file test/test.o sample.o $(LDFLAGS)

test.o:
	$(CPP) -c -o test/$@ test/*.c $(CPPFLAGS)


.PHONY: run-test
run-test: test
	test/testfile

.PHONY: run-test-clean
run-test-clean: clean test
	test/testfile

.PHONY: clean
clean:
	@echo "clean..."
	rm -f test/*.exe *.o test/*.o
