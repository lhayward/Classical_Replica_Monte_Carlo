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

//typdefs needed because uint and ulong are return types:
typedef Hypercube::uint uint;

/*************************** Hypercube(int L, int D) (constructor) ***************************/
Hypercube::Hypercube(uint L, uint D)
  : Lattice(L)
{
  D_ = D;
  z_ = 2*D;
  initNAndNeighbours();
}

/************************ Hypercube(std::ifstream* fin) (constructor) ************************/
Hypercube::Hypercube(std::ifstream* fin)
  : Lattice(fin)
{
  const char EQUALS_CHAR = '=';
  
  //read in D from the file:
  if( fin!=NULL && fin->is_open() )
  { D_ = FileReading::readUint(fin, EQUALS_CHAR); }
  else
  {
    std::cout << "Error in Hypercube constructor: could not read from file" << std::endl;
    D_=1;
  }
  
  z_ = 2*D_;
  initNAndNeighbours();
}

/********************************* ~Hypercube() (destructor) *********************************/
Hypercube::~Hypercube()
{
  //delete the neighbours_ array:
  for(uint i=0; i<N_; i++)
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
  N_ = uintPower(L_,D_);
  
  //initialize the neighbours_ array (note periodic boundary conditions):
  neighbours_ = new uint*[N_];
  for( uint i=0; i<N_; i++ )
  { 
    neighbours_[i] = new uint[D_];
    for( uint j=0; j<D_; j++ ) 
    {
      neighbours_[i][j] = i + uintPower(L_,j);
      //fix at the boundaries:
      if( neighbours_[i][j]%uintPower(L_,(j+1)) < uintPower(L_,j) )
      { neighbours_[i][j] -= uintPower(L_,(j+1)); }
    } //j
  } //i
}

/******************************** uintPower(int base, int exp) *******************************/
uint Hypercube::uintPower(uint base, uint exp)
{
  uint result = 1;
  for(uint i=1; i<=exp; i++)
  { result *= base; } 
  
  return result;
} //uintPower method

/****************************************** print() ******************************************/
void Hypercube::print()
{
  std::cout << "Hypercube Parameters:\n"
            << "           Lattice Length L = " << L_ << "\n"
            << "                Dimension D = " << D_ << "\n"
            << "  Number of Lattice Sites N = " << N_ << "\n"
            << "  Neighbours list:" << std::endl;
  
  //print the neighbours_ array:
  for( uint i=0; i<N_; i++ )
  {
    std::cout.width(4);
    std::cout << "    " << i << ": ";
    for( uint j=0; j<D_; j++ )
    {
      std::cout.width(4);
      std::cout << neighbours_[i][j] << " ";
    } //j
    std::cout << std::endl;
  } //i 
  std::cout << std::endl;
} //print method

/*********************************** Public Getter Methods: **********************************/
uint Hypercube::getD(){ return D_; }
