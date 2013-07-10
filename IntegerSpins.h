/*********************************************************************************************
************************************ CLASSICAL MONTE CODE ************************************
**********************************************************************************************
* Lauren Hayward
**********************************************************************************************
* File:   IntegerSpins.h (Abstract Class)
*********************************************************************************************/

#ifndef INTEGERSPINS_H
#define INTEGERSPINS_H

#include "MersenneTwister.h"

class IntegerSpins 
{
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
    
    //pure virtual functions:
    virtual void randomize(MTRand* randomGen) = 0;
    virtual void randomize(MTRand* randomGen, bool* regionA) = 0;
};

#endif  // INTEGERSPINS_H
