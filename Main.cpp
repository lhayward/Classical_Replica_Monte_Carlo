/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File: Main.cpp
* Note: MersenneTwister.h was taken from external sources and is used as the random number
*       generator
**********************************************************************************************/

//#include <cmath>
#include <ctime>
//#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "FileReading.h"
#include "Hypercube.h"
#include "MersenneTwister.h"
#include "Lattice.h"
#include "Model.h"
#include "SimParameters.h"

typedef unsigned long ulong;

std::string getFileSuffix(int argc, char** argv);
Lattice* readLattice(std::string latticeName, std::string fileName, std::string startStr);

/**********************************************************************************************
******************************************** main *********************************************
**********************************************************************************************/
int main(int argc, char** argv) 
{
  MTRand randomGen;
  SimParameters* params;
  Lattice* lattice;
  Model* model;     
  
  //variables related to input data from files:
  std::string fileSuffix      = getFileSuffix( argc, argv );
  std::string paramFileName   = "params" + fileSuffix + ".txt";
  std::string simParamStr     = "SIMULATION PARAMETERS";
  std::string latticeParamStr = "LATTICE PARAMETERS";
  std::string modelParamStr   = "MODEL PARAMETERS";
  
  std::cout.precision(8);
  std::cout << "\n***STARTING SIMULATION***\n" << std::endl;
  std::cout << "Parameter File: " << paramFileName << std::endl;
  
  params = new SimParameters(paramFileName, simParamStr);
  params->print();
  
  lattice = readLattice(params->getLatticeType(), paramFileName, latticeParamStr);
  lattice->print();
  
  model = new Model(paramFileName,modelParamStr);
  model->print();
  
  /*
  //initialize the model based on the model name specified in the parameter file:
  if( params->getModelName() == "toriccode" )
  {
    std::cout << "TORIC CODE!" << std::endl;
    model = new Model(modelParamFileName);
    model->print();
  }
  */
  
  std::cout << "\n***END OF SIMULATION***\n" << std::endl;
  return 0;
} //closes main

/**************************** getFileSuffix(int argc, char** argv) ***************************/
std::string getFileSuffix(int argc, char** argv)
{
  std::string result = "";
  
  if( argc > 1 )
  { result = "_" + std::string(argv[1]); }
  
  return result;
}

/****** readLattice(std::string latticeName, std::string fileName, std::string startStr) *****/
Lattice* readLattice(std::string latticeName, std::string fileName, std::string startStr)
{
  std::ifstream fin;
  fin.open(fileName.c_str());
  
  if( fin.is_open() )
  { FileReading::readUntilFound(&fin, startStr); }
  
  return new Hypercube(&fin);
}