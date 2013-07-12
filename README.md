Classical_Replica_Monte_Carlo
=============================

Compile using make (generates executable classicalmc).
Run program using ./classicalmc [filePrefix]

Note that filePrefix is an optional argument such that the simulation parameters are stored in
- the file "simParams_filePrefix.txt" if filePrefix is specified
- the file "simParams.txt" if filePrefix is not specified 

An example of a valid simulation parameter file is:

Temperature List = [2.5, 2, 1.3, 1.0]
Random Generator Seed = 20140802
Number of Warm-up Sweeps = 100
Number of Sweeps per Energy Measurement = 1
Number of Measurements per Bin = 1000
Number of Bins = 100
Model Name = toriccode     
