Classical_Replica_Monte_Carlo
=============================

Compile using "make" (generates executable "classicalmc").  
Run program using "./classicalmc [filePrefix]"

Note that filePrefix is an optional argument as explained below. 

The simulation parameters are stored in:
- the file "simParams_filePrefix.txt" if filePrefix is specified
- the file "simParams.txt" if filePrefix is not specified 

The model-specific parameters are stored in:
- the file "[modelName]Params_filePrefix.txt" if filePrefix is specified  
- the file "[modelName]Params.txt" if filePrefix is not specified  

where modelName is read in from the simParams files

An example of a valid simulation parameter file is:

Temperature List = [2.5, 2, 1.3, 1.0]  
Random Generator Seed = 20140802  
Number of Warm-up Sweeps = 100  
Number of Sweeps per Energy Measurement = 1  
Number of Measurements per Bin = 1000  
Number of Bins = 100  
Model Name = toriccode     

An example of a valid model parameter file is (toriccodeParams.txt):

Coupling J = 1  
Lattice Length L = 3  
Number of Replicas alpha = 2  
Fraction of Columns in Region A = 0.5  


