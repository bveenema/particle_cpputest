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
#CPPFLAGS += -D TESTING

LDFLAGS := -L$(CPPUTEST_HOME)/cpputest_build/lib -lCppUTest

TESTDIR = test
SRCDIR = src

TEST_FILES := $(wildcard $(TESTDIR)/*.cpp)
OBJ_FILES := $(addprefix test/,$(notdir $(TEST_FILES:.cpp=.o)))

OBJECTS = test.o


# Additional compiled test program
test: $(OBJ_FILES)
	$(CPP) -o test/$@ $^ $(LDFLAGS)

$(TESTDIR)/%.o: %.cpp
	$(CPP) -c -o $@ $(CPPFLAGS)


.PHONY: run-test
run-test: test
	$(TESTDIR)/test.exe

.PHONY: run-test-clean
run-test-clean: clean run-test

.PHONY: clean
clean:
	@echo "clean..."
	rm -f test/*.exe *.o test/*.o
