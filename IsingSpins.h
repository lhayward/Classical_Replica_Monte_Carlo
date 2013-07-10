/*********************************************************************************************
************************************ CLASSICAL MONTE CODE ************************************
**********************************************************************************************
* Lauren Hayward
**********************************************************************************************
* File:   IsingSpins.h 
*********************************************************************************************/

#ifndef ISINGSPINS_H
#define ISINGSPINS_H

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

#endif  // ISINGSPINS_H