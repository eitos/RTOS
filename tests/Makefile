MAIN_DIR = ../EiTOS
GTEST_DIR = gtest-1.7.0
SOURCES  = $(MAIN_DIR)/src/OS.cpp $(MAIN_DIR)/src/mutex.cpp $(MAIN_DIR)/ports/mock/port/port.cpp
TESTS = tests_run_all.cpp priorityQueue.cpp swapTable.cpp

PORT_INCLUDE = ../EiTOS/ports/mock/
SRC_INCLUDE = ../EiTOS/src/include
INCLUDES = -I$(GTEST_DIR)/include -I$(PORT_INCLUDE) -I../EiTOS/include -I.. -I$(SRC_INCLUDE)

LIBS_FOLDERS = -L$(GTEST_DIR)/lib/.libs
GTEST_LIBS = $(GTEST_DIR)/lib/.libs/libgtest.a
LIBS = -pthread -lgtest

CXX = g++
CXXFLAGS = -ggdb

PHONY=all test run clean

all: test run

gtest.zip :
	wget http://googletest.googlecode.com/files/gtest-1.7.0.zip -O gtest.zip

gtest-1.7.0: gtest.zip
	unzip -o  gtest.zip
	cd gtest-1.7.0; ./configure
	make -C gtest-1.7.0

test: gtest-1.7.0
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS_FOLDERS) $(GTEST_LIBS) $(SOURCES) $(TESTS) -o test $(LIBS)

run: test
	LD_LIBRARY_PATH=gtest-1.7.0/lib/.libs:$LD_LIBRARY_PATH  ./test
	rm -f test

clean:
	rm -f test
	rm -Rf gtest-1.7.0


