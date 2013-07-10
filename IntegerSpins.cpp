/*********************************************************************************************
************************************ CLASSICAL MONTE CODE ************************************
**********************************************************************************************
* Lauren Hayward
**********************************************************************************************
* File:   IntegerSpins.cpp (Abstract Class)
*********************************************************************************************/

#include <iostream>
#include "IntegerSpins.h"

/**************** IntegerSpins::IntegerSpins(int alpha, int N) (constructor) *****************
* Input: alpha (number of replicas), N (number of spins per replica)
* This constructor initializes the array of spin degrees of freedom 
*********************************************************************************************/
IntegerSpins::IntegerSpins(int alpha, int N)
{
  int a; 
  
  this->alpha_ = alpha;
  this->N_     = N;
  
  spins_ = new spin_type*[alpha_];
  for( a=0; a<alpha_; a++ )
  { spins_[a] = new spin_type[N_]; }
  
  this->polarize(); //Initially, all spins have value +1
}

/************************ IntegerSpins::~IntegerSpins() (destructor) ************************/
IntegerSpins::~IntegerSpins()
{ 
  int a;
  
  for(a=0; a<alpha_; a++)
  {delete[] spins_[a]; }
  delete[] spins_;
}

/********************************* IntegerSpins::polarize() **********************************
* This function gives each spin the value +1 so that the lattice is polarized.
*********************************************************************************************/
void IntegerSpins::polarize()
{
  int a,i;
  
  for( a=0; a<alpha_; a++ )
  {
    for( i=0; i<N_; i++ )
    { spins_[a][i] = 1; }
  }
}


/********************************** IntegerSpins::print() ***********************************/
void IntegerSpins::print()
{
  int a, i;
  
  for(a=0; a<alpha_; a++)
  {
    std::cout << "Replica #" << (a+1) << ":" << std::endl;
    for(i=0; i<N_; i++)
    { 
      std::cout.width(2);
      std::cout << spins_[a][i] << " "; 
    }
    std::cout << std::endl;
  }
}
