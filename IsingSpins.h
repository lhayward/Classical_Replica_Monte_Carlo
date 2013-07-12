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
    IsingSpins(int alpha, int N);
    virtual ~IsingSpins();
    
    virtual void randomize(MTRand* randomGen);
    virtual void randomize(MTRand* randomGen, bool* regionA);
};

#endif  // ISING_SPINS_H