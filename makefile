#!make -f
#id:322530080 mail:avishb1213@gmail.com
CXX=g++
CXXFLAGS=-std=c++11 -g  -Wall  

SD=demo.cpp Catan.cpp Player.cpp Board.cpp Resource.cpp 
ST=Catan.cpp Player.cpp Board.cpp Resource.cpp TestCounter.cpp test.cpp
OD=$(subst .cpp,.o,$(SD))
OT=$(subst .cpp,.o,$(ST))

.PHONY: all run demo test valgrind clean

all: demo test

run_test: test
	./$^ < input_test.txt

catan: demo
	./$^ < input_demo.txt

demo: demo.o $(OD)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o test.o $(OT)
	$(CXX) $(CXXFLAGS) $^ -o test

valgrind_test: test
	valgrind ./test < input_test.txt

valgrind_demo: demo
	valgrind ./demo < input_demo.txt

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test