CXX = g++
INC =-I'C://Program Files//boost//include//boost_1_68//'

main: main.o utility.o
	$(CXX) $(INC) -o main main.o utility.o 'C://Program Files//boost//lib//libboost_filesystem-mgw48-mt-d-x64-1_68.a' 'C://Program Files//boost//lib//libboost_system-mgw48-mt-d-x64-1_68.a'

main.o: main.cpp utility.h
	$(CXX) -c main.cpp

utility.o: utility.cpp utility.h
	$(CXX) $(INC) -c utility.cpp