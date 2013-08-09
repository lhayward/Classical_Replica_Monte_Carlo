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

/****************************************** print() ******************************************/
void IsingModel::print()
{
  std::cout << "Ising Model Parameters:\n"
            << "                        Coupling J: " << J_ << "\n"
            << "          Number of Replicas alpha: " << alpha_ << "\n"
            << "   Fraction of Columns in Region A: " << fracA_ << "\n"
            << std::endl;
}