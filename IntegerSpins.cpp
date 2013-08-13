/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IntegerSpins.cpp (Abstract Class)
**********************************************************************************************/

#include <iostream>
#include "IntegerSpins.h"

/************************ IntegerSpins(int alpha, int N) (constructor) ************************
* Input: alpha (number of replicas), N (number of spins per replica)
* This constructor initializes the array of spin degrees of freedom 
**********************************************************************************************/
IntegerSpins::IntegerSpins(int alpha, int N)
{
  alpha_ = alpha;
  N_     = N;
  
  spins_ = new spin_type*[alpha_];
  for( uint a=0; a<alpha_; a++ )
  { spins_[a] = new spin_type[N_]; }
  
  polarize(); //Initially, all spins have value +1
}

/******************************** ~IntegerSpins() (destructor) *******************************/
IntegerSpins::~IntegerSpins()
{ 
  if( spins_!=NULL)
  {
    for(uint a=0; a<alpha_; a++)
    {delete[] spins_[a]; }
    delete[] spins_;
  }
  spins_=NULL;
}

/***************************************** polarize() *****************************************
* This method gives each spin the value +1 so that the lattice is polarized.
**********************************************************************************************/
void IntegerSpins::polarize()
{
  for( uint a=0; a<alpha_; a++ )
  {
    for( uint i=0; i<N_; i++ )
    { spins_[a][i] = 1; }
  } //a
} //polarize method


/****************************************** print() ******************************************/
void IntegerSpins::print()
{
  for(int a=0; a<alpha_; a++)
  {
    std::cout << "Replica #" << (a+1) << ":" << std::endl;
    for(uint i=0; i<N_; i++)
    { 
      std::cout.width(2);
      std::cout << spins_[a][i] << " "; 
    }
    std::cout << std::endl;
  } //a
} //print method
