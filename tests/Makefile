MAIN_DIR = ../
GTEST_DIR = gtest-1.7.0
SOURCES  = ../EiTOS/src/Task.cpp
TESTS = tests_run_all.cpp scheduler.cpp

PORT_INCLUDE = ../EiTOS/ports/mock/
INCLUDES = -I$(GTEST_DIR)/include -I$(PORT_INCLUDE) -I../EiTOS/include -I..

LIBS_FOLDERS = -L$(GTEST_DIR)/lib/.libs
LIBS = -lgtest

CXX = g++
CXXFLAGS = -g

test:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS_FOLDERS) $(SOURCES) $(TESTS) $(LIBS) -o test
	./test

clean:
	rm test