CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o func.o list.o hash.o
	$(CC)	main.o func.o list.o hash.o -o main.exe
main.o : main.cpp func.h list.h hash.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
func.o : func.cpp func.h
	$(CC) -c func.cpp -o func.o $(CFLAGS)
list.o : list.cpp list.h
	$(CC) -c list.cpp -o list.o $(CFLAG)
hash.o : hash.cpp hash.h
	$(CC) -c hash.cpp -o hash.o $(CFLAGS)

clean:
	rm *.o main.exe
