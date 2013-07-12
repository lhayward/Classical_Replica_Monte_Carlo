CC = c++ -Wall -funroll-loops #-pg #-xHOST # -O3

PROG = classicalmc
HDRS = MersenneTwister.h FileReading.h Hypercube.h IntegerSpins.h IsingSpins.h Lattice.h SimParameters.h
SRCS = Main.cpp FileReading.cpp Hypercube.cpp IntegerSpins.cpp IsingSpins.cpp Lattice.cpp SimParameters.cpp
OBJS = Main.o FileReading.o Hypercube.o IntegerSpins.o IsingSpins.o Lattice.o SimParameters.o

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	
FileReading.o: FileReading.cpp $(HDRS)
	$(CC) -c FileReading.cpp -o FileReading.o

Hypercube.o: Hypercube.cpp $(HDRS)
	$(CC) -c Hypercube.cpp -o Hypercube.o

IntegerSpins.o: IntegerSpins.cpp $(HDRS)
	$(CC) -c IntegerSpins.cpp -o IntegerSpins.o

IsingSpins.o: IsingSpins.cpp $(HDRS)
	$(CC) -c IsingSpins.cpp -o IsingSpins.o
	
Lattice.o: Lattice.cpp $(HDRS)
	$(CC) -c Lattice.cpp -o Lattice.o

SimParameters.o: SimParameters.cpp $(HDRS)
	$(CC) -c SimParameters.cpp -o SimParameters.o

Main.o: Main.cpp $(HDRS)
	$(CC) -c Main.cpp -o Main.o 

clean:
	rm -f $(PROG) $(OBJS) 
