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
//#include <sstream>
#include "MersenneTwister.h"
#include "IsingSpins.h"
#include "Hypercube.h"
#include "SimParameters.h"

typedef unsigned long ulong;

/**********************************************************************************************
******************************************** main *********************************************
**********************************************************************************************/
int main(int argc, char** argv) 
{
  MTRand randomGen;
  
  std::cout << "\n***STARTING SIMULATION***\n" << std::endl;
  
  SimParameters* params = new SimParameters("sim_params.txt");
  params->print();
  
  IsingSpins* spins = new IsingSpins(1,5);
  spins->print();
  //Hypercube* cube = new Hypercube(2,3);
  //cube->print();
  
  std::cout << "\n***END OF SIMULATION***\n" << std::endl;
  return 0;
} //closes main
