CC = c++ -Wall -funroll-loops #-pg #-xHOST # -O3

PROG = classicalmc
HDRS = MersenneTwister.h FileReading.h Hypercube.h IntegerSpins.h IsingModel.h IsingSpins.h Lattice.h Measure.h Model.h SimParameters.h ToricCode_1_q.h
SRCS = Main.cpp FileReading.cpp Hypercube.cpp IntegerSpins.cpp IsingModel.cpp IsingSpins.cpp Lattice.cpp Measure.cpp Model.cpp SimParameters.cpp ToricCode_1_q.cpp
OBJS = Main.o FileReading.o Hypercube.o IntegerSpins.o IsingModel.o IsingSpins.o Lattice.o Measure.o Model.o SimParameters.o ToricCode_1_q.o

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	
FileReading.o: FileReading.cpp $(HDRS)
	$(CC) -c FileReading.cpp -o FileReading.o
	
Hypercube.o: Hypercube.cpp $(HDRS)
	$(CC) -c Hypercube.cpp -o Hypercube.o
	
IntegerSpins.o: IntegerSpins.cpp $(HDRS)
	$(CC) -c IntegerSpins.cpp -o IntegerSpins.o
	
IsingModel.o: IsingModel.cpp $(HDRS)
	$(CC) -c IsingModel.cpp -o IsingModel.o
	
IsingSpins.o: IsingSpins.cpp $(HDRS)
	$(CC) -c IsingSpins.cpp -o IsingSpins.o
	
Lattice.o: Lattice.cpp $(HDRS)
	$(CC) -c Lattice.cpp -o Lattice.o
	
Measure.o: Measure.cpp $(HDRS)
	$(CC) -c Measure.cpp -o Measure.o
	
Model.o: Model.cpp $(HDRS)
	$(CC) -c Model.cpp -o Model.o
	
SimParameters.o: SimParameters.cpp $(HDRS)
	$(CC) -c SimParameters.cpp -o SimParameters.o
	
ToricCode_1_q.o: ToricCode_1_q.cpp $(HDRS)
	$(CC) -c ToricCode_1_q.cpp -o ToricCode_1_q.o
	
Main.o: Main.cpp $(HDRS)
	$(CC) -c Main.cpp -o Main.o 
	
clean:
	rm -f $(PROG) $(OBJS) 
