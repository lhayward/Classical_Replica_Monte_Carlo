/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   SimParameters.h
**********************************************************************************************/

#ifndef SIM_PARAMETERS_H
#define SIM_PARAMETERS_H

#include <fstream>
#include <string>
#include <vector>

class SimParameters 
{ 
  public:
    typedef unsigned int  uint;
    typedef unsigned long ulong;
    
  private: 
    std::vector<double>* TList_;  //list of temperatures
    ulong                seed_;
    uint                 numWarmUpSweeps_;
    uint                 sweepsPerMeas_;
    uint                 measPerBin_;
    uint                 numBins_;
    std::string          modelName_;  //name of the Hamiltonian 
                                      //(eg. "ising", "toriccode", etc.)
    
  public:
    SimParameters(std::string fileName);
    virtual ~SimParameters();
    
    void print();
    
    //getter methods:
    double      getTemperature    (uint i);
    uint        getNumWarmUpSweeps();
    uint        getSweepsPerMeas  ();
    uint        getMeasPerBin     ();
    uint        getNumBins        ();
    std::string getModelName      ();
};

#endif  // SIM_PARAMETERS_H
