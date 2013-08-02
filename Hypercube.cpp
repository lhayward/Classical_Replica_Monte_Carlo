/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Hypercube.cpp
**********************************************************************************************/

#include <iostream>
#include "FileReading.h"
#include "Hypercube.h"

/*************************** Hypercube(int L, int D) (constructor) ***************************/
Hypercube::Hypercube(int L, int D)
  : Lattice(L)
{
  D_ = D;
  initNAndNeighbours();
}

Hypercube::Hypercube(std::ifstream* fin)
  : Lattice(fin)
{
  const char EQUALS_CHAR = '=';
  
  if( fin!=NULL && fin->is_open() )
  { D_ = FileReading::readUint(fin, EQUALS_CHAR); }
  else
  {
    std::cout << "Error in Hypercube constructor: could not read from file" << std::endl;
    D_=1;
  }
  initNAndNeighbours();
  //N_ = intPower(L_,D_);
}

/********************************* ~Hypercube() (destructor) *********************************/
Hypercube::~Hypercube()
{
  //delete the neighbours_ array:
  for(int i=0; i<N_; i++)
  { 
    if( neighbours_[i] != NULL )
    { delete[] neighbours_[i]; }
    neighbours_[i] = NULL; 
  }
  if( neighbours_ != NULL )
  { delete[] neighbours_; }
  neighbours_ = NULL;
} // ~Hypercube

/************************************ initNAndNeighbours() ***********************************/
void Hypercube::initNAndNeighbours()
{
  N_ = intPower(L_,D_);
  
  //initialize the neighbours_ array (Note periodic boundary conditions):
  neighbours_ = new int*[N_];
  for( int i=0; i<N_; i++ )
  { 
    neighbours_[i] = new int[D_];
    for( int j=0; j<D_; j++ ) 
    {
      neighbours_[i][j] = i + intPower(L_,j);
      //fix at the boundaries:
      if( neighbours_[i][j]%intPower(L_,(j+1)) < intPower(L_,j) )
      { neighbours_[i][j] -= intPower(L_,(j+1)); }
    } //j
  } //i
}

/******************************** intPower(int base, int exp) ********************************/
int Hypercube::intPower(int base, int exp)
{
  int result=0;
  
  if( exp >= 0 )
  {
    result = 1;
    for(int i=exp; i>=1; i--)
    { result *= base; } 
  }
  
  return result;
} //intPower method

/****************************************** print() ******************************************/
void Hypercube::print()
{
  std::cout << "Hypercube with:\n"
            << "  L = " << L_ << "\n"
            << "  D = " << D_ << "\n"
            << "  N = " << N_ << "\n"
            << "  Neighbours list:" << std::endl;
  
  //print the neighbours_ array:
  for( int i=0; i<N_; i++ )
  {
    std::cout.width(4);
    std::cout << "    " << i << ": ";
    for( int j=0; j<D_; j++ )
    {
      std::cout.width(4);
      std::cout << neighbours_[i][j] << " ";
    } //j
    std::cout << std::endl;
  } //i 
} //print method
