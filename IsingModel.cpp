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

/***************** IsingModel(std::string fileName) (constructor) *****************/
IsingModel::IsingModel(std::ifstream* fin, Lattice* lattice)
  : Model(fin)
{
  lattice_ = lattice;
}

/*************************** ~IsingModel() (destructor) ***************************/
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

/************************************* singleSpinUpdate() ************************************/
void IsingModel::singleSpinUpdate()
{
}