/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   SimParameters.cpp
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "FileReading.h"
#include "SimParameters.h"

//typdefs needed because uint and ulong are return types:
typedef SimParameters::uint  uint;
typedef SimParameters::ulong ulong; 

/********** SimParameters(std::string fileName, std::string startStr) (constructor) **********/
SimParameters::SimParameters(std::string fileName, std::string startStr)
{
  const char EQUALS_CHAR = '=';
  const char LIST_START_CHAR = '[';
  const char LIST_END_CHAR = ']';
  
  isValid_=true;
  TList_ = new std::vector<double>;
  
  std::ifstream fin;
  fin.open(fileName.c_str());
  
  if( fin.is_open() )
  {
    FileReading::readUntilFound(&fin, startStr);
    
    TList_           = FileReading::readDoubleVec(&fin, EQUALS_CHAR, LIST_START_CHAR, 
                                                  LIST_END_CHAR);
    seed_            = FileReading::readULong    (&fin, EQUALS_CHAR);
    numWarmUpSweeps_ = FileReading::readUint     (&fin, EQUALS_CHAR);
    sweepsPerMeas_   = FileReading::readUint     (&fin, EQUALS_CHAR);
    measPerBin_      = FileReading::readUint     (&fin, EQUALS_CHAR);
    numBins_         = FileReading::readUint     (&fin, EQUALS_CHAR);
    latticeType_     = FileReading::readString   (&fin, EQUALS_CHAR);
    modelName_       = FileReading::readString   (&fin, EQUALS_CHAR);
    
    randomGen_       = new MTRand(seed_);
  }
  else
  { 
    std::cout << "ERROR in SimParameters constructor: could not find file \"" << fileName 
              << "\"\n" << std::endl; 
    isValid_=false;
  }
  
  fin.close();
} //SimParameters constructor

/******************************* ~SimParameters() (destructor) *******************************/
SimParameters::~SimParameters()
{
  if(TList_!=NULL)
  { delete TList_; }
  TList_ = NULL; 
}

/****************************************** print() ******************************************/
void SimParameters::print()
{
  if( isValid_ )
  {
      std::cout << "Simulation Parameters:\n"
                << "---------------------\n"
                << "           Temperature List = [ ";
  
      //print the list of temperatures:
      for( uint i=0; i<(TList_->size() - 1); i++ )
      { std::cout << TList_->at(i) << ", "; }
  
      //print the last temperature element:
      if( TList_->size() > 0 )
      { std::cout << TList_->at(TList_->size() - 1); }
      std::cout << " ]\n";
  
      //print the rest of the parameters:
      std::cout << "                       Seed = " << seed_ << "\n"
                << "   Number of Warm-up Sweeps = " << numWarmUpSweeps_ << "\n"
                << "     Sweeps per Measurement = " << sweepsPerMeas_ << "\n"
                << "       Measurements per Bin = " << measPerBin_ << "\n"
                << "             Number of Bins = " << numBins_ << "\n"
                << "               Lattice Type = " << latticeType_ << "\n"
                << "                 Model Name = " << modelName_ << "\n"
                << std::endl;   
  }
  else
  {
    std::cout << "ERROR in SimParameters::print(): could not print because the SimParameters "
              << "object is not valid\n" << std::endl;
  }
  
} //print method

/***************************************** isValid() ******************************************
* Public getter methods for the isValid_ parameter
**********************************************************************************************/
bool SimParameters::isValid()      
{ return isValid_; }
