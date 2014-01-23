Classical_Replica_Monte_Carlo
=============================

Compile using "make" (generates executable "classicalmc").  
Run program using "./classicalmc [filePrefix]"

Note that filePrefix is an optional argument as explained below. 

The simulation parameters are stored in:
- the file "params_filePrefix.txt" if filePrefix is specified
- the file "params.txt" if filePrefix is not specified 

The choices for Region A are:
- "cylinder, {d}" where d is is a number with 0<=d<=1

An example of a valid parameter file is:

\#SIMULATION PARAMETERS:  
Temperature List = [2.5, 2, 1.3, 1.0]  
Random Generator Seed = 20140802  
Number of Warm-up Sweeps = 100  
Number of Sweeps per Energy Measurement = 1  
Number of Measurements per Bin = 1000  
Number of Bins = 100  
Lattice Type = hypercube  
Model Name = toriccode  

\#LATTICE PARAMETERS:  
Lattice Length L = 4  
Lattice Dimension D = 2  

\#MODEL PARAMETERS:  
Coupling J = 1  
Number of Replicas alpha = 2  
Region A = KP, C  


