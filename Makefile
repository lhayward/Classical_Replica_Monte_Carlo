CC = c++ -Wall -funroll-loops #-pg #-xHOST # -O3

PROG = classicalmc
HDRS = MersenneTwister.h IntegerSpins.h IsingSpins.h
SRCS = Main.cpp IntegerSpins.cpp IsingSpins.cpp
OBJS = Main.o IntegerSpins.o IsingSpins.cpp

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)
	
IntegerSpins.o: IntegerSpins.cpp $(HDRS)
	$(CC) -c IntegerSpins.cpp -o IntegerSpins.o

IsingSpins.o: IsingSpins.cpp $(HDRS)
	$(CC) -c IsingSpins.cpp -o IsingSpins.o

Main.o: Main.cpp $(HDRS)
	$(CC) -c Main.cpp -o Main.o 

clean:
	rm -f $(PROG) $(OBJS) 
