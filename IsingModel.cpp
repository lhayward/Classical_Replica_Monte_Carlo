/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IsingModel.cpp
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include "FileReading.h"
#include "IsingModel.h"

/*********************** IsingModel(std::string fileName) (constructor) **********************/
IsingModel::IsingModel(std::ifstream* fin, Lattice* lattice)
  : Model(fin)
{
  //temporary variables:
  uint currNeigh;
  
  //object variables:
  lattice_ = lattice;
  z_ = lattice_->getZ();
  
  if( z_%2 != 0 )
  { 
    std::cout << "ERROR in IsingModel constructor: The lattice must have an even number of "
              << "nearest neighbours.\n" << std::endl; 
  }
  else
  {  
    N_ = lattice_->getN();
    regionA_ = lattice_->getRegionA(fracA_);
    
    numProbs_ = (z_*alpha_)/2;
    singleUpdateProbs_ = new double[numProbs_];
    //initialize the singleUpdateProbs_ array:
    for( uint i=0; i<numProbs_; i++ )
    { singleUpdateProbs_[i] = 0; }
    
    //initialize the allNeighbours_ array using the neighbours list stored in the lattice_:
    allNeighbours_ = new uint*[N_];
    for( uint i=0; i<N_; i++ )
    { allNeighbours_[i] = new uint[z_]; }
    for( uint i=0; i<N_; i++ )
    { 
      for( uint j=0; j<(z_/2); j++ ) 
      {
        currNeigh = lattice_->getNeighbour(i,j);
        allNeighbours_[i]        [j]         = currNeigh;
        allNeighbours_[currNeigh][j + (z_/2)] = i;
      } //j
    } //i
    
    spins_ = new IsingSpins(alpha_, N_);
  }
}

/********************************* ~IsingModel() (destructor) ********************************/
IsingModel::~IsingModel()
{
  if( allNeighbours_ != NULL )
  {
    for(uint i=0; i<N_; i++)
    { delete[] allNeighbours_[i]; }
    delete[] allNeighbours_; 
  }
  allNeighbours_ = NULL; 
  
  if(singleUpdateProbs_!=NULL)
  { delete[] singleUpdateProbs_; }
  singleUpdateProbs_ = NULL;
  
  if(spins_!=NULL)
  { delete spins_; }
  spins_ = NULL;
}

/************************************* calculateEnergy() *************************************/
double IsingModel::calculateEnergy()
{
  int    nnSum;
  double energy=0;

  //***Need to write an access method to get spins_[a][i]:
  /* 
  for( uint a=0; a<alpha_; a++ )
  {
    for( uint i=0; i<N_; i++ )
    {   
      nnSum=0;
      for( uint j=0; j<(z_/2); j++ )
      { nnSum += spins_[a][allNeighbours_[i][j]]; } 
      energy += -J_*spins_[a][i]*nnSum;
    }
  }
  */
  return energy;
}

/****************************************** print() ******************************************/
void IsingModel::print()
{
  std::cout << "Ising Model Parameters:\n" 
            << "----------------------" << std::endl;
  Model::print();
}

/************************************* printNeighbours() *************************************/
void IsingModel::printNeighbours()
{
  std::cout << "IsingModel Neighbours list:" << std::endl;
  
  //print the neighbours_ array:
  for( uint i=0; i<N_; i++ )
  {
    std::cout.width(4);
    std::cout << "    " << i << ": ";
    for( uint j=0; j<z_; j++ )
    {
      std::cout.width(4);
      std::cout << allNeighbours_[i][j] << " ";
    } //j
    std::cout << std::endl;
  } //i 
  std::cout << std::endl;
} //printNeighbours method

/******************************** randomize(MTRand* randomGen) *******************************/
void IsingModel::randomize(MTRand* randomGen)
{ spins_->randomize(randomGen, regionA_); }

/************************************* setT(double newT) *************************************/
void IsingModel::setT(double newT)
{ 
  Model::setT(newT); 
  
  //update the singleUpdateProbs_ array:
  for( uint i=0; i<numProbs_; i++ )
  { singleUpdateProbs_[i] = exp(-abs(J_)*2*(2*(i+1))/T_); }
}

/************************************* singleSpinUpdate() ************************************/
void IsingModel::singleSpinUpdate()
{
}