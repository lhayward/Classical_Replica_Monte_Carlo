/*********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE ********************************
**********************************************************************************************
* Lauren Hayward
**********************************************************************************************
* File:   IsingSpins.cpp 
*********************************************************************************************/

#include <iostream>
#include "IsingSpins.h"

/****************** IsingSpins::IsingSpins(int alpha, int N) (constructor) ******************/
IsingSpins::IsingSpins(int alpha, int N)
  : IntegerSpins(alpha, N)
{ }

/************************** IsingSpins::~IsingSpins() (destructor) **************************/
IsingSpins::~IsingSpins(){ } 

/************************* IsingSpins::randomize(MTRand* randomGen) **************************
* This function gives each spin in every replica a random value (either -1 or +1).
*********************************************************************************************/
void IsingSpins::randomize(MTRand* randomGen)
{
  for( int a=0; a<alpha_; a++ )
  {
    for( int i=0; i<N_; i++ )
    { spins_[a][i] = 2*( randomGen->randInt(1) ) - 1; }
  }
}

/***************** IsingSpins::randomize(MTRand* randomGen, bool* regionA) *******************
* This function gives each spin in every replica a random value (either -1 or +1) with the 
* constraint that all spins in region A must have the same value in all replicas.
*********************************************************************************************/
void IsingSpins::randomize(MTRand* randomGen, bool* regionA)
{
  //Give each spin in the first replica a random value (either -1 or +1):
  for( int i=0; i<N_; i++ )
  { spins_[0][i] = 2*( randomGen->randInt(1) ) - 1; }
  
  //For all remaining replicas, each spin in region A must have the same value as its 
  //corresponding spin in the first replica. Spins in region B will have (uncorrelated)
  //random values:
  for( int a=1; a<alpha_; a++ )
  {
    for( int i=0; i<N_; i++ )
    {
      if( regionA[i] )
      { spins_[a][i] = spins_[0][i]; }
      else
      { spins_[a][i] = 2*( randomGen->randInt(1) ) - 1; }
    }
  }
}