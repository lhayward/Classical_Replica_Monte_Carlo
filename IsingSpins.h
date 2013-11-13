/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IsingSpins.h 
**********************************************************************************************/

#ifndef ISING_SPINS_H
#define ISING_SPINS_H

#include "IntegerSpins.h"
#include "MersenneTwister.h"

class IsingSpins: public IntegerSpins
{
  public:
    IsingSpins(uint alpha, uint N);
    virtual ~IsingSpins();
    
    virtual void randomize(MTRand* randomGen);
    virtual void randomize(MTRand* randomGen, bool* regionA);
    
    void flip(uint latticeSite, uint replicaStart, uint replicaEnd);
};

#endif  // ISING_SPINS_H