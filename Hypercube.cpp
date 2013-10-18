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

//typdef needed because uint is a return types:
typedef Hypercube::uint uint;

/*************************** Hypercube(int L, int D) (constructor) ***************************/
Hypercube::Hypercube(uint L, uint D)
  : Lattice(L)
{
  isValid_=true;
  D_ = D;
  z_ = 2*D;
  init_N_and_neighbours();
}

/************* Hypercube(std::ifstream* fin, std::string fileName) (constructor) *************/
Hypercube::Hypercube(std::ifstream* fin, std::string fileName)
  : Lattice(fin, fileName)
{
  const char EQUALS_CHAR = '=';
  
  isValid_ = true;
  
  //read in D from the file:
  if( fin!=NULL && fin->is_open() )
  { D_ = FileReading::readUint(fin, EQUALS_CHAR); }
  else
  {
    std::cout << "ERROR in Hypercube constructor: could not read from file \"" << fileName 
              << "\"\n" << std::endl;
    D_=1;
    isValid_ = false;
  }
  
  z_ = 2*D_;
  init_N_and_neighbours();
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

/********************************** init_N_and_neighbours() **********************************/
void Hypercube::init_N_and_neighbours()
{
  if( isValid_ )
  {
    N_ = uintPower(L_,D_);
  
    //initialize the neighbours_ array (note periodic boundary conditions):
    neighbours_ = new uint*[N_];
    for( uint i=0; i<N_; i++ )
    { neighbours_[i] = new uint[2*D_]; }
    for( uint i=0; i<N_; i++ )
    { 
      for( uint j=0; j<D_; j++ ) 
      {
        neighbours_[i][j] = i + uintPower(L_,j);
        //fix at the boundaries:
        if( neighbours_[i][j]%uintPower(L_,(j+1)) < uintPower(L_,j) )
        { neighbours_[i][j] -= uintPower(L_,(j+1)); }
        
        //initialize the corresponding neighbour (note that this information is redundant for a
        //hypercube, but we include it since some Model classes won't assume a hypercubic 
        //lattice)
        neighbours_[ neighbours_[i][j] ] [j + D_] = i;
      } //j
    } //i
  }
  else
  {
    std::cout << "ERROR in Hypercube::init_N_and_neighbours(): the Hypercube object is not "
              << "valid\n" << std::endl;
  }
}

/******************************************* round ******************************************/
int Hypercube::round(double num)
{
    int result;
    
    if( num < 0.0 )
    { result = (int)ceil(num - 0.5); }
    else
    { result = (int)floor(num + 0.5); }
    
    return result;
}

/******************************** uintPower(int base, int exp) *******************************/
uint Hypercube::uintPower(uint base, uint exp)
{
  uint result = 1;
  for(uint i=1; i<=exp; i++)
  { result *= base; } 
  
  return result;
} //uintPower method

/******************************** getNeighbour(uint i, uint j) *******************************/
uint Hypercube::getNeighbour(uint i, uint j)
{
  uint result = 0;
  
  if( (neighbours_ != NULL) && i<N_ && j<(2*D_) )
  { result = neighbours_[i][j]; }
  else
  { 
    std::cout << "ERROR in Hypercube::getNeighbour(uint i, uint j): NULL neighbours_ array or "
              << "index out of bounds" << std::endl; 
  }
  
  return result;
}

/********************************** getRegionA(double fracA) *********************************/
bool* Hypercube::getRegionA(double fracA)
{ 
  bool* regionA = new bool[N_];
  
  uint NRows = (uint)round(fracA*L_);
  uint NInA = NRows*L_;
  
  for( uint i=0; i<NInA; i++ )
  { regionA[i] = 1; }
  for( uint i=NInA; i<N_; i++ )
  { regionA[i] = 0; }
  
  return regionA;
}

/*************************************** printParams() ***************************************/
void Hypercube::printParams()
{
  if( isValid_ )
  {
    std::cout << "Hypercube Parameters:\n"
              << "--------------------\n"
              << "           Lattice Length L = " << L_ << "\n"
              << "                Dimension D = " << D_ << "\n"
              << "  Number of Lattice Sites N = " << N_ << "\n"
              << std::endl;
  }
  else
  {
    std::cout << "ERROR in Hypercube::printParams(): the Hypercube object is not valid\n" 
             << std::endl;
  }
  
} //printParams method

/****************************************** printNeighbours() ******************************************/
void Hypercube::printNeighbours()
{
  if( isValid_ )
  {
    std::cout << "Hypercube Neighbours list:" << std::endl;
  
    //print the neighbours_ array:
    for( uint i=0; i<N_; i++ )
    {
      std::cout.width(4);
      std::cout << "    " << i << ": ";
      for( uint j=0; j<(2*D_); j++ )
      {
        std::cout.width(4);
        std::cout << neighbours_[i][j] << " ";
      } //j
      std::cout << std::endl;
    } //i 
    std::cout << std::endl;
  }
  else
  {
    std::cout << "ERROR in Hypercube::printNeighbours(): the Hypercube object is not valid\n" 
              << std::endl;
  }
} //printNeighbours method

/*********************************** Public Getter Methods: **********************************/
uint Hypercube::getD(){ return D_; }
