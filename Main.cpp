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
#include <iostream>
#include <string>
#include "MersenneTwister.h"
#include "SimParameters.h"

typedef unsigned long ulong;

std::string getFileSuffix(int argc, char** argv);

/**********************************************************************************************
******************************************** main *********************************************
**********************************************************************************************/
int main(int argc, char** argv) 
{
  MTRand      randomGen;
  
  //variables related to input file names:
  std::string fileSuffix = getFileSuffix( argc, argv );
  std::string simParamFileName = "simParams" + fileSuffix + ".txt";
  std::string modelParamFileName;
  
  std::cout.precision(8);
  std::cout << "\n***STARTING SIMULATION***\n" << std::endl;
  
  std::cout << "Simulation Parameter File: " << simParamFileName << std::endl;
  
  SimParameters* params = new SimParameters(simParamFileName);
  params->print();
  
  //initialize the model based on the model name specified in the parameter file:
  modelParamFileName = params->getModelName() + fileSuffix + ".txt";
  if( params->getModelName() == "toriccode" )
  {
    std::cout << "TORIC CODE!" << std::endl;
  }
  
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