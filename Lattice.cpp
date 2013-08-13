/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Lattice.cpp (Abstract Class)
**********************************************************************************************/

#include <iostream>
#include "FileReading.h"
#include "Lattice.h"

//typdef needed because uint is a return types:
typedef Lattice::uint uint;

/******************************** Lattice(int L) (constructor) *******************************/
Lattice::Lattice(uint L)
{
  L_ = L;
  N_ = 0;
  neighbours_ = NULL;
}

Lattice::Lattice(std::ifstream* fin)
{
  const char EQUALS_CHAR = '=';
  
  if( fin!=NULL && fin->is_open() )
  { L_ = FileReading::readUint(fin, EQUALS_CHAR); }
  else
  {
    std::cout << "ERROR in Lattice constructor: could not read from file\n" << std::endl;
    L_=0;
  }
  
  N_ = 0;
  neighbours_ = NULL;
}

/********************************** ~Lattice() (destructor) **********************************/
Lattice::~Lattice()
{
  if( neighbours_ != NULL )
  {
    for(uint i=0; i<N_; i++)
    { delete[] neighbours_[i]; }
    delete[] neighbours_; 
  }
  neighbours_=NULL;
}

/*********************************** Public Getter Methods: **********************************/
uint Lattice::getN(){ return N_; }
uint Lattice::getZ(){ return z_; }