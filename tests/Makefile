MAIN_DIR = ../EiTOS
GTEST_DIR = gtest-1.7.0
SOURCES  = $(MAIN_DIR)/src/task.cpp $(MAIN_DIR)/src/schedulerQueue.cpp
TESTS = tests_run_all.cpp scheduler.cpp

PORT_INCLUDE = ../EiTOS/ports/mock/
INCLUDES = -I$(GTEST_DIR)/include -I$(PORT_INCLUDE) -I../EiTOS/include -I..

LIBS_FOLDERS = -L$(GTEST_DIR)/lib/.libs
GTEST_LIBS = $(GTEST_DIR)/lib/.libs/libgtest.a
LIBS = -pthread -lgtest

CXX = g++
CXXFLAGS = -g --static

all: bootstrap test clean

bootstrap:
	wget http://googletest.googlecode.com/files/gtest-1.7.0.zip
	unzip  gtest-1.7.0.zip
	cd gtest-1.7.0; \
	./configure; \
	make
	rm -Rf gtest-1.7.0.zip

test:	
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS_FOLDERS) $(GTEST_LIBS) $(SOURCES) $(TESTS) -o test $(LIBS)
	./test

clean:
	rm -f test
	rm -Rf gtest-1.7.0
	rm -Rf gtest-1.7.0.zip*


