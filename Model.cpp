/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Model.cpp (Abstract Class)
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include "FileReading.h"
#include "Model.h"

/************************* Model(std::string fileName) (constructor) *************************/
Model::Model(std::ifstream* fin)
{ 
  const char EQUALS_CHAR = '=';
  
  if( fin!=NULL && fin->is_open() )
  {
    J_     = FileReading::readDouble(fin, EQUALS_CHAR);
    alpha_ = FileReading::readUint  (fin, EQUALS_CHAR);
    fracA_ = FileReading::readDouble(fin, EQUALS_CHAR);
  }
  else
  { 
    std::cout << "ERROR in Model constructor: could not read from file\n" << std::endl; 
  }
  
  //initialize the temperature (should be changed by user to desired temperature before
  //starting the simulation):
  T_ = 1.0;
}

/*********************************** ~Model() (destructor) ***********************************/
Model::~Model()
{ }

/****************************************** print() ******************************************/
void Model::print()
{
  std::cout << "                       Coupling J = " << J_ << "\n"
            << "         Number of Replicas alpha = " << alpha_ << "\n"
            << "  Fraction of Columns in Region A = " << fracA_ << "\n"
            << std::endl;
}

/************************************* setT(double newT) *************************************/
void Model::setT(double newT)
{ T_ = newT; }