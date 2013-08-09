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
  neighbours_ = NULL;
}

Lattice::Lattice(std::ifstream* fin)
{
  const char EQUALS_CHAR = '=';
  
  if( fin!=NULL && fin->is_open() )
  { L_ = FileReading::readUint(fin, EQUALS_CHAR); }
  else
  {
    std::cout << "Error in Lattice constructor: could not read from file" << std::endl;
    L_=0;
  }
}

/********************************** ~Lattice() (destructor) **********************************/
Lattice::~Lattice()
{ }

/*********************************** Public Getter Methods: **********************************/
uint Lattice::getN(){ return N_; }
uint Lattice::getZ(){ return z_; }