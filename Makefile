CPP=g++

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = googletest/googletest

# Where to find user code.
USER_DIR = .

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = SEGMENT_TREE_TEST

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h                                 \
                $(GTEST_DIR)/include/gtest/internal/*.h


COMMON_FLAGS=-I. -Igoogletest/googletest/include/ -pipe -Wall -Wextra          \
             -Wextra -Wconversion -march=native
CPP_LIBS=-Llib -Lgoogletest/build/googlemock/gtest/
CPPFLAGS=-ggdb -O1 $(COMMON_FLAGS) -std=c++0x -isystem                         \
         -I$(GTEST_DIR)/include

EXEC=test.out

QUICK_EXEC=qtest.out

SOURCES=segment-tree-test.cpp

OBJECTS=segment-tree-test.o

HEADERS=SegmentTree.hpp                                                        \
        $(GTEST_HEADERS)



all:$(EXEC) $(QUICK_EXEC)

$(EXEC): $(OBJECTS) gtest_main.a
	$(CPP) $(CPPFLAGS) -flto -pthread $(OBJECTS) gtest_main.a -o $(EXEC)

$(QUICK_EXEC): quick-test.cpp
	$(CPP) $(CPPFLAGS) -DSEGMENT_TREE_DEBUG quick-test.cpp -o $(QUICK_EXEC)

%.o:%.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC) $(OLIB)
	rm -f *.out
	rm -f *.o
	rm -f $(TESTS) gtest.a gtest_main.a
	rm -f *.a


# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
