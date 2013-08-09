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
  lattice_ = lattice;
  z_ = lattice_->getZ();
  
  if( z_%2 != 0 )
  { 
    std::cout << "ERROR in IsingModel constructor: The lattice must have an even number of "
              << "nearest neighbours.\n" << std::endl; 
  }
  else
  {  
    numProbs_ = (z_*alpha_)/2;
    singleUpdateProbs = new double[numProbs_];
  }
}

/********************************* ~IsingModel() (destructor) ********************************/
IsingModel::~IsingModel()
{ }

/************************************* calculateEnergy() *************************************/
double IsingModel::calculateEnergy()
{
  return 0;
}

/****************************************** print() ******************************************/
void IsingModel::print()
{
  std::cout << "Ising Model Parameters:" << std::endl;
  Model::print();
}

/************************************* setT(double newT) *************************************/
void IsingModel::setT(double newT)
{ 
  Model::setT(newT); 
  
  //update the singleUpDateProbs array:
  for( uint i=0; i<numProbs_; i++ )
  { singleUpdateProbs[i] = exp(-abs(J_)*2*(2*(i+1))/T_); }
}

/************************************* singleSpinUpdate() ************************************/
void IsingModel::singleSpinUpdate()
{
}