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

/*********** IsingModel(std::ifstream* fin, std::string fileName, Lattice* lattice) ***********
**************************************** (constructor) ***************************************/
IsingModel::IsingModel(std::ifstream* fin, std::string fileName, Lattice* lattice)
  : Model(fin, fileName)
{
  if( isValid_ )  //check that parent is valid (read from file correctly)
  {
    if( lattice != NULL && lattice->isValid() )
    {
      //temporary variables:
      uint currNeigh;
  
      //object variables:
      lattice_ = lattice;
      z_ = lattice_->getZ();
  
      if( z_%2 == 0 )
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
            allNeighbours_[i]        [j]          = currNeigh;
            allNeighbours_[currNeigh][j + (z_/2)] = i;
          } //j
        } //i
    
        spins_ = new IsingSpins(alpha_, N_);
      } 
      else
      { 
        std::cout << "ERROR in IsingModel constructor: The lattice must have an even number of "
                  << "nearest neighbours.\n" << std::endl; 
        isValid_ = false;
      }
    }
    else
    {
      std::cout << "ERROR in IsingModel constructor: The passed Lattice object is not valid\n"
                << std::endl; 
      isValid_ = false;
    }
  } 
  else
  {
    std::cout << "ERROR in IsingModel constructor: the parent Model object is not valid\n"
              << std::endl;
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
  double energy=0;
  
  if( isValid_ )
  {
    //int    nnSum;

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
  }
  else
  {
    std::cout << "ERROR in IsingModel::calculateEnergy(): the IsingModel object is not valid\n" 
              << std::endl;
  }
  
  return energy;
}

/****************************************** print() ******************************************/
void IsingModel::print()
{
  if( isValid_ )
  {
    std::cout << "Ising Model Parameters:\n" 
              << "----------------------" << std::endl;
    Model::print();
  }
  else
  {
    std::cout << "ERROR in IsingModel::print(): the IsingModel object is not valid\n" 
              << std::endl;
  }
}

/************************************* printNeighbours() *************************************/
void IsingModel::printNeighbours()
{
  if( isValid_ )
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
  }
  else
  {
    std::cout << "ERROR in IsingModel::printNeighbours(): the IsingModel object is not valid\n" 
              << std::endl;
  }
} //printNeighbours method

/******************************** randomize(MTRand* randomGen) *******************************/
void IsingModel::randomize(MTRand* randomGen)
{ 
  if( isValid_ )
  {
    spins_->randomize(randomGen, regionA_);
  }
  else
  {
    std::cout << "ERROR in IsingModel::randomize(MTRand* randomGen): the IsingModel object is "
              << "not valid\n" << std::endl;
  }
}

/************************************* setT(double newT) *************************************/
void IsingModel::setT(double newT)
{ 
  if( isValid_ )
  {
    Model::setT(newT); 
  
    //update the singleUpdateProbs_ array:
    for( uint i=0; i<numProbs_; i++ )
    { singleUpdateProbs_[i] = exp(-abs(J_)*2*(2*(i+1))/T_); }
  }
  else
  {
    std::cout << "ERROR in IsingModel::setT(double newT): the IsingModel object is not valid\n"
              << std::endl;
  }
}

/************************************* singleSpinUpdate() ************************************/
void IsingModel::singleSpinUpdate()
{
}