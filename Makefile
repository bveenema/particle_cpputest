# makefile for sample cpputest
CPPUTEST_HOME = c:/cygwin/home/bveenema/cpputest-3.8

# CPPUTest is C++Write, so using g++ To compile the test file
CPP       	:= g++
CPPFLAGS  	:= -g -Wall
CPPFLAGS  	+= -I $(CPPUTEST_HOME)/include
CPPFLAGS  	+= -I src

LDFLAGS 		:= -L $(CPPUTEST_HOME)/cpputest_build/lib -l CppUTest

TESTDIR 		= test
SRCDIR 			= src

SRC_FILES 	:= $(wildcard $(SRCDIR)/*.cpp)
SRC_OBJ 		:= $(addprefix $(SRCDIR)/,$(notdir $(SRC_FILES:.cpp=.o)))

TEST_FILES 	:= $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJ 		:= $(addprefix $(TESTDIR)/,$(notdir $(TEST_FILES:.cpp=.o)))

OBJECTS = test.o

src: $(SRC_OBJ)

$(SRCDIR)/%.o: %.cpp
	$(eval CPPFLAGS += -D TESTING)
	$(CPP) -c -o $@ $(CPPFLAGS)

# Additional compiled test program
test: $(TEST_OBJ)
	$(CPP) -o $(TESTDIR)/$@ src/currentSense.o $^ $(LDFLAGS)

$(TESTDIR)/%.o: %.cpp
	$(CPP) -c -o $@ $(CPPFLAGS)


.PHONY: set-testing-flag
set-testing-flag:
	$(eval CPPFLAGS += -D TESTING)

.PHONY: run-test
run-test: set-testing-flag src test
	$(TESTDIR)/test.exe

.PHONY: run-test-clean
run-test-clean: clean run-test

.PHONY: clean
clean:
	@echo "clean..."
	rm -f test/*.exe *.o test/*.o src/*.o
