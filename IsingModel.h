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
    uint        numProbs_; //number of elements in the singleUpdateProbs array
    uint        z_; //number of nearest neighbours for each spin
                    //NOTE: We assume z_ is an even, positive integer
    uint        N_; //total number of degrees of freedom
    double*     singleUpdateProbs_; //the exponentials needed for the single-spin updates 
                                   //(pre-computed to save time)
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    Lattice*    lattice_; //the lattice on which the d.o.f. live
    
  public:
    IsingModel(std::ifstream* fin, std::string fileName, Lattice* lattice);
    virtual ~IsingModel();
    
    virtual double calculateEnergy ();
    virtual void   printParams     ();
    virtual void   printSpins      ();
    virtual void   randomize       (MTRand* randomGen);
    virtual void   setT            (double newT);
    virtual void   singleSpinUpdate();
};

#endif  // ISINGMODEL_H
