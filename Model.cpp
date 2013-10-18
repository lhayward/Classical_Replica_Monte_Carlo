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

/*************** Model(std::ifstream* fin, std::string fileName) (constructor) ***************/
Model::Model(std::ifstream* fin, std::string fileName)
{ 
  const char EQUALS_CHAR = '=';
  
  isValid_ = true;  //so far parent is valid
  
  if( fin!=NULL && fin->is_open() )
  {
    J_     = FileReading::readDouble(fin, EQUALS_CHAR);
    alpha_ = FileReading::readUint  (fin, EQUALS_CHAR);
    fracA_ = FileReading::readDouble(fin, EQUALS_CHAR);
  }
  else
  { 
    std::cout << "ERROR in Model constructor: could not read from file \"" << fileName 
              << "\"\n" << std::endl; 
    isValid_ = false;
  }
  
  regionA_=NULL;
  //initialize the temperature (should be changed by user to desired temperature before
  //starting the simulation):
  T_ = 1.0;
}

/*********************************** ~Model() (destructor) ***********************************/
Model::~Model()
{
  if(regionA_!=NULL)
  { delete[] regionA_; }
  regionA_ = NULL; 
}

/*************************************** printParams() ***************************************/
void Model::printParams()
{
  if( isValid_ )
  {
    std::cout << "                       Coupling J = " << J_ << "\n"
              << "         Number of Replicas alpha = " << alpha_ << "\n"
              << "  Fraction of Columns in Region A = " << fracA_ << "\n"
              << std::endl;
  }
  else
  {
    std::cout << "ERROR in Model::printParams(): the Model object is not valid\n" << std::endl;
  }
}

/************************************* setT(double newT) *************************************/
void Model::setT(double newT)
{ T_ = newT; }