MAIN_DIR = ../EiTOS
GTEST_DIR = gtest-1.7.0
SOURCES  = $(MAIN_DIR)/src/Task.cpp $(MAIN_DIR)/src/schedulerQueue.cpp
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
	rm -f test