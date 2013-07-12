CC = c++ -Wall -funroll-loops #-pg #-xHOST # -O3

PROG = classicalmc
HDRS = MersenneTwister.h IntegerSpins.h IsingSpins.h Lattice.h Hypercube.h
SRCS = Main.cpp IntegerSpins.cpp IsingSpins.cpp Lattice.cpp Hypercube.cpp
OBJS = Main.o IntegerSpins.o IsingSpins.o Lattice.o Hypercube.o

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

Hypercube.o: Hypercube.cpp $(HDRS)
	$(CC) -c Hypercube.cpp -o Hypercube.o

IntegerSpins.o: IntegerSpins.cpp $(HDRS)
	$(CC) -c IntegerSpins.cpp -o IntegerSpins.o

IsingSpins.o: IsingSpins.cpp $(HDRS)
	$(CC) -c IsingSpins.cpp -o IsingSpins.o
	
Lattice.o: Lattice.cpp $(HDRS)
	$(CC) -c Lattice.cpp -o Lattice.o

Main.o: Main.cpp $(HDRS)
	$(CC) -c Main.cpp -o Main.o 

clean:
	rm -f $(PROG) $(OBJS) 
