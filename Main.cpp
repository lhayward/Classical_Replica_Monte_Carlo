/*********************************************************************************************
************************************ CLASSICAL MONTE CODE ************************************
**********************************************************************************************
* Lauren Hayward
**********************************************************************************************
* File: Main.cpp
* Note: MersenneTwister.h was taken from external sources and is used as the random number
*       generator
*********************************************************************************************/

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MersenneTwister.h"
#include "IsingSpins.h"

typedef unsigned long ulong;

/*********************************************************************************************
******************************************** main ********************************************
*********************************************************************************************/
int main(int argc, char** argv) 
{
  MTRand randomGen;
  int N=4;
  
  bool* regA = new bool[4];
  
  for (int i=0; i<4; i++ )
  { regA[i] = 1; }
  regA[3]=0;
  
  std::cout << "\n***STARTING SIMULATION***\n" << std::endl;
  
  //randomGen.seed(12345);
  IsingSpins* spins  = new IsingSpins(2,N);
  
  spins->randomize(&randomGen, regA);
  spins->print();
  
  delete spins;
  
  std::cout << "\n***END OF SIMULATION***\n" << std::endl;
  return 0;
} //closes main
