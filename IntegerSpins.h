/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IntegerSpins.h (Abstract Class)
**********************************************************************************************/

#ifndef INTEGER_SPINS_H
#define INTEGER_SPINS_H

#include "MersenneTwister.h"

class IntegerSpins 
{
  public:
    typedef int spin_type;  //spins are integers here
  
  protected:
    int         alpha_;   //total number of replicas
    int         N_;       //number of spins per replica
    spin_type** spins_;   //multi-dimensional array of the spin degrees of freedom
    
  public:
    IntegerSpins(int alpha, int N);
    virtual ~IntegerSpins();
    
    void polarize();
    void print();
    
    //pure virtual method:
    virtual void randomize(MTRand* randomGen) = 0;
    virtual void randomize(MTRand* randomGen, bool* regionA) = 0;
};

#endif  // INTEGER_SPINS_H
