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
#include "FileReading.h"
#include "ToricCode_q1_GeneralD.h"

/***************** ToricCode_q1_GeneralD(std::string fileName) (constructor) *****************/
/*ToricCode_q1_GeneralD::ToricCode_q1_GeneralD(std::ifstream* fin, Hypercube* lattice)
  : Model(fin)
{
  std::cout << "TC Constructor, Hypercube" << std::endl;
}*/


/***************** ToricCode_q1_GeneralD(std::string fileName) (constructor) *****************/
ToricCode_q1_GeneralD::ToricCode_q1_GeneralD(std::ifstream* fin, Lattice* lattice)
  : Model(fin)
{
  lattice = dynamic_cast<Hypercube *>(lattice);
  if(!lattice)
  {
    std::cout << "Could not convert to Hypercube." << std::endl;
  }
  else
  { std::cout <<"YAY!" << std::endl; }
}

/*************************** ~ToricCode_q1_GeneralD() (destructor) ***************************/
ToricCode_q1_GeneralD::~ToricCode_q1_GeneralD()
{ }

/****************************************** print() ******************************************/
void ToricCode_q1_GeneralD::print()
{
  std::cout << "(1,D-1) Toric Code with:\n"
            << "                        Coupling J: " << J_ << "\n"
            << "          Number of Replicas alpha: " << alpha_ << "\n"
            << "   Fraction of Columns in Region A: " << fracA_ << "\n"
            << std::endl;
}