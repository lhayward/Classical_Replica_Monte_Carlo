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
    bool isValid_; //whether or not this is a valid SimParameters object
    std::vector<double>* TList_;  //list of temperatures
    ulong                seed_;
    uint                 numWarmUpSweeps_;
    uint                 sweepsPerMeas_;
    uint                 measPerBin_;
    uint                 numBins_;
    std::string          latticeType_;  //type of lattice on which to perform the simulation
                                        //(eg. "hypercube", "kagome", etc.)
    std::string          modelName_;  //name of the Hamiltonian 
                                      //(eg. "ising", "toriccode", etc.)
    
  public:
    SimParameters(std::string fileName, std::string startStr);
    virtual ~SimParameters();
    
    void print();
    
    //getter methods:
    bool        isValid           ();
    double      getTemperature    (uint i);
    uint        getNumWarmUpSweeps();
    uint        getSweepsPerMeas  ();
    uint        getMeasPerBin     ();
    uint        getNumBins        ();
    std::string getLatticeType    ();
    std::string getModelName      ();
};

#endif  // SIM_PARAMETERS_H
