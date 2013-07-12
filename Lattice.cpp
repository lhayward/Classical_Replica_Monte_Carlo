/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Lattice.cpp (Abstract Class)
**********************************************************************************************/

#include <iostream>
#include "Lattice.h"

/******************************** Lattice(int L) (constructor) *******************************/
Lattice::Lattice(int L)
{
  L_ = L;
  neighbours_ = NULL;
}

/********************************** ~Lattice() (destructor) **********************************/
Lattice::~Lattice()
{ }
