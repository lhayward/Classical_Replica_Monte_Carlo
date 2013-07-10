/*********************************************************************************************
************************************ CLASSICAL MONTE CODE ************************************
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
  int a,i;
  
  for( a=0; a<alpha_; a++ )
  {
    for( i=0; i<N_; i++ )
    { spins_[a][i] = 2*( randomGen->randInt(1) ) - 1; }
  }
}

/***************** IsingSpins::randomize(MTRand* randomGen, bool* regionA) ******************/
void IsingSpins::randomize(MTRand* randomGen, bool* regionA)
{
  int a,i;
  
  //Give each spin in the first replica a random value (either -1 or +1):
  for( i=0; i<N_; i++ )
  { spins_[0][i] = 2*( randomGen->randInt(1) ) - 1; }
  
  //For all remaining replicas, each spin in region A must have the same value as its 
  //corresponding spin in the first replica. Spins in region B will have (uncorrelated)
  //random values:
  for( a=1; a<alpha_; a++ )
  {
    for( i=0; i<N_; i++ )
    {
      if( regionA[i] )
      { spins_[a][i] = spins_[0][i]; }
      else
      { spins_[a][i] = 2*( randomGen->randInt(1) ) - 1; }
    }
  }
}