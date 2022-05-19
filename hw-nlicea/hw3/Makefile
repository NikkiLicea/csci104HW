CXX := g++
CXXFLAGS := -g -Wall --std=c++11
GTESTINCL := -I /usr/include/gtest/  
GTESTLIBS := -lgtest -lgtest_main  -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: rh llrec-test

llrec-test: llrec-test.cpp llrec.o
	$(CXX) $(CXXFLAGS) $(GTESTINCL)  -o $@ $^ $(GTESTLIBS)

stack: stack_test.cpp stack.h
	$(CXX) $(CXXFLAGS) $(GTESTINCL)  -o $@ $^ $(GTESTLIBS)

# generic rule for .cpp files
board.o : board.cpp board.h vehicle.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
heur.o : heur.cpp heur.h board.h vehicle.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
move.o : move.cpp move.h board.h heur.h vehicle.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
solver.o : solver.cpp solver.h move.h board.h heur.h vehicle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
llrec.o : llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 
rh : rh.cpp board.o heur.o move.o solver.o
	$(CXX) $(CXXFLAGS) $^ -o $@ 

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------




clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 