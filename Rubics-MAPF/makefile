CC = g++
CFLAGS  = -g -Wall


all: solver


solver:  test.o Cube.o Solver2.o Indexer.o PDBBuilder.o
	$(CC) $(CFLAGS) -o solver test.o Cube.o Solver2.o Indexer.o PDBBuilder.o

test.o:  test.cpp
	$(CC) $(CFLAGS) -c test.cpp

Cube.o:  Cube.cpp Cube.h
	$(CC) $(CFLAGS) -c Cube.cpp

Solver2.o: Solver2.cpp Solver2.h
	$(CC) $(CFLAGS) -c Solver2.cpp

Indexer.o: Indexer.cpp Indexer.h
	$(CC) $(CFLAGS) -c Indexer.cpp

PDBBuilder.o: PDBBuilder.cpp PDBBuilder.h
	$(CC) $(CFLAGS) -c PDBBuilder.cpp

clean: 
	$(RM) solver *.o *~