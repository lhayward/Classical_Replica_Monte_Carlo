/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   ToricCode_q1_GeneralD.cpp
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include "FileReading.h"
#include "ToricCode_q1_GeneralD.h"

/***************** ToricCode_q1_GeneralD(std::string fileName) (constructor) *****************/
ToricCode_q1_GeneralD::ToricCode_q1_GeneralD(std::ifstream* fin, Lattice* lattice)
  : Model(fin)
{
  lattice_ = dynamic_cast<Hypercube *>(lattice);
  if(!lattice_)
  {
    std::cout << "ERROR in ToricCode_q1_GeneralD constructor:\n" 
              << "  A lattice of type Hypercube is required.\n"
              << "  A lattice of type " << typeid(*lattice).name() << " was given.\n" 
              << std::endl;
  }
}

/*************************** ~ToricCode_q1_GeneralD() (destructor) ***************************/
ToricCode_q1_GeneralD::~ToricCode_q1_GeneralD()
{ }

/************************************* calculateEnergy() *************************************/
double ToricCode_q1_GeneralD::calculateEnergy()
{
  return 0;
}

/****************************************** print() ******************************************/
void ToricCode_q1_GeneralD::print()
{
  std::cout << "(1,D-1) Toric Code Parameters:\n"
            << "                        Coupling J: " << J_ << "\n"
            << "          Number of Replicas alpha: " << alpha_ << "\n"
            << "   Fraction of Columns in Region A: " << fracA_ << "\n"
            << std::endl;
}

/************************************* singleSpinUpdate() ************************************/
void ToricCode_q1_GeneralD::singleSpinUpdate()
{
}