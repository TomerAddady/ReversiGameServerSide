# Tomer Addady 
# 207162678

a.out: compileAll
	g++ *.o -o ../../exe/server.out -pthread 
	rm -f *.o

compileAll: *.h *.cpp
	g++  -c *.cpp -pthread
