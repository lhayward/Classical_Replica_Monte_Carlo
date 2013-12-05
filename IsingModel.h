/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IsingModel.h
*
* Notes:  
*   - We assume that each site on the lattice has an even number of nearest neighbours 
*     (if this needs to change, modify the singleUpdateProbs array)
**********************************************************************************************/

#ifndef ISINGMODEL_H
#define ISINGMODEL_H

#include <string>
#include "Hypercube.h"
#include "IsingSpins.h"
#include "Model.h"

class IsingModel : public Model
{ 
  public:
    typedef unsigned int  uint;
    
  private:
    uint        z_; //number of nearest neighbours for each spin
                    //NOTE: We assume z_ is an even, positive integer
    uint        N_; //total number of degrees of freedom
    
    uint        numProbs_; //number of elements in the singleUpdateProbs array
    double*     singleUpdateProbs_; //the exponentials needed for the single-spin updates 
                                    //(pre-computed to save time)
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    Lattice*    lattice_; //the lattice on which the d.o.f. live
    
  public:
    IsingModel(std::ifstream* fin, std::string outFileName, Lattice* lattice);
    virtual ~IsingModel();
    
    virtual void printParams    ();
    virtual void printRegionA   ();
    virtual void printSpins     ();
    virtual void randomize      (MTRand* randomGen);
    virtual void setT           (double newT);
    virtual void sweep          (MTRand* randomGen);
    virtual void updateEnergy   ();
    virtual void writeBin       (int binNum, int numMeas);
};

#endif  // ISINGMODEL_H
