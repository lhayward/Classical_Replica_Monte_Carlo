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
    std::cout << "Error in Model constructor: could not read from file" << std::endl; 
  }
}

/*********************************** ~Model() (destructor) ***********************************/
Model::~Model()
{ }