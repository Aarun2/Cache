
output: cache.o
	g++ cache.o -o output

cache.o: cache.cpp
	g++ -c cache.cpp

clean:
	rm *.o output