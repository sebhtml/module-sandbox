CXX=g++
CXXFLAGS=-O3 -g -Wall -std=c++98

all:
	$(CXX) $(CXXFLAGS) Core.cpp -o core -ldl
	$(CXX) $(CXXFLAGS) -c -fPIC Module1.cpp -o Module1.o
	$(CXX) -shared Module1.o -o Module1.so 
	$(CXX) $(CXXFLAGS) -c -fPIC Module2.cpp -o Module2.o
	$(CXX) -shared Module2.o -o Module2.so 
	$(CXX) $(CXXFLAGS) -c -fPIC Module3.cpp -o Module3.o
	$(CXX) -shared Module3.o -o Module3.so 
	
test:
	./core configuration.conf
