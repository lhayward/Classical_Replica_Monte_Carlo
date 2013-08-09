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
#include <typeinfo>
#include "FileReading.h"
#include "Hypercube.h"
#include "IsingModel.h"
#include "MersenneTwister.h"
#include "Lattice.h"
#include "Model.h"
#include "SimParameters.h"
#include "ToricCode_q1_GeneralD.h"

typedef unsigned long ulong;

std::string getFileSuffix(int argc, char** argv);
Lattice* readLattice(std::string latticeName, std::string fileName, std::string startStr);
Model* readModel(std::string modelName, std::string fileName, std::string startStr, 
                 Lattice* lattice);

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
  
  std::cout << "Parameter File: " << paramFileName << "\n" << std::endl;
  
  params = new SimParameters(paramFileName, simParamStr);
  params->print();
  
  lattice = readLattice(params->getLatticeType(), paramFileName, latticeParamStr);
  lattice->print();
  
  model = readModel(params->getModelName(), paramFileName, modelParamStr, lattice);
  model->print();
  
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

/******** readModel(std::string modelName, std::string fileName, std::string startStr) *******/
Model* readModel(std::string modelName, std::string fileName, std::string startStr, 
                 Lattice* lattice)
{
  Model* result=NULL;
  std::ifstream fin;
  fin.open(fileName.c_str());
  
  if( fin.is_open() )
  { FileReading::readUntilFound(&fin, startStr); }
  
  if( modelName == "isingmodel" )
  { result = new IsingModel(&fin, lattice); }
  else if( modelName == "toriccode" )
  { result = new ToricCode_q1_GeneralD(&fin, lattice); }
  
  return result;
}