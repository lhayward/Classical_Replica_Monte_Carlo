/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IsingSpins.cpp 
**********************************************************************************************/

#include <iostream>
#include "IntegerSpins.h"
#include "IsingSpins.h"
#include "MersenneTwister.h"

/************************ IsingSpins(uint alpha, uint N) (constructor) ***********************/
IsingSpins::IsingSpins(uint alpha, uint N)
  : IntegerSpins(alpha, N)
{ }

/********************************* ~IsingSpins() (destructor) ********************************/
IsingSpins::~IsingSpins(){ } 

/******************************** randomize(MTRand* randomGen) ********************************
* This method gives each spin in every replica a random value (either -1 or +1).
**********************************************************************************************/
void IsingSpins::randomize(MTRand* randomGen)
{
  for( uint a=0; a<alpha_; a++ )
  {
    for( uint i=0; i<N_; i++ )
    { spins_[a][i] = 2*( randomGen->randInt(1) ) - 1; }
  } //a
} //randomize method

/***************** flip(uint latticeSite, uint replicaStart, uint replicaEnd) ****************/
void IsingSpins::flip(uint latticeSite, uint replicaStart, uint replicaEnd)
{
  for( uint a=replicaStart; a<=replicaEnd; a++ )
  { spins_[a][latticeSite] *= -1; }
}

/************************ randomize(MTRand* randomGen, bool* regionA) *************************
* This method gives each spin in every replica a random value (either -1 or +1) with the
* constraint that all spins in region A (as determined from the input regionA array) must have
* the same value in all replicas.
* NOTE: This method assumes that the length of the passed regionA array is equal to N_ (the 
*       number of spins per replica.
**********************************************************************************************/
void IsingSpins::randomize(MTRand* randomGen, bool* regionA)
{
  //Give each spin in the first replica a random value (either -1 or +1):
  for( uint i=0; i<N_; i++ )
  { spins_[0][i] = 2*( randomGen->randInt(1) ) - 1; }
  
  //For all remaining replicas, each spin in region A must have the same value as its 
  //corresponding spin in the first replica. Spins in region B will have (uncorrelated)
  //random values:
  for( uint a=1; a<alpha_; a++ )
  {
    for( uint i=0; i<N_; i++ )
    {
      if( regionA[i] )
      { spins_[a][i] = spins_[0][i]; }
      else
      { spins_[a][i] = 2*( randomGen->randInt(1) ) - 1; }
    } //i
  } //a
} //randomize method