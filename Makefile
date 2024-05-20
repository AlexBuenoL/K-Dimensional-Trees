CXX = g++
CXXFLAGS = -std=c++11 -Wall

kdtree: KDTree.o main.o
	$(CXX) $(CXXFLAGS) -o kdtree KDTree.o main.o

KDTree.o: KDTree.cc KDTree.hh
	$(CXX) $(CXXFLAGS) -c KDTree.cc

main.o: main.cc KDTree.hh
	$(CXX) $(CXXFLAGS) -c main.cc

clean:
	rm -f *.o kdtree
