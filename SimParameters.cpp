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

/********************* SimParameters(std::string fileName) (constructor) *********************/
SimParameters::SimParameters(std::string fileName)
{
  const char EQUALS_CHAR = '=';
  const char LIST_START_CHAR = '[';
  const char LIST_END_CHAR = ']';
  
  std::ifstream fin;
  
  TList_ = new std::vector<double>;
  
  fin.open(fileName.c_str());
  
  if( fin.is_open() )
  {
    TList_           = FileReading::readDoubleList(&fin, EQUALS_CHAR, LIST_START_CHAR, LIST_END_CHAR);
    seed_            = FileReading::readLongInt(&fin, EQUALS_CHAR);
    numWarmUpSweeps_ = FileReading::readUint   (&fin, EQUALS_CHAR);
    sweepsPerMeas_   = FileReading::readUint   (&fin, EQUALS_CHAR);
    measPerBin_      = FileReading::readUint   (&fin, EQUALS_CHAR);
    numBins_         = FileReading::readUint   (&fin, EQUALS_CHAR);
    modelName_       = FileReading::readString (&fin, EQUALS_CHAR);
  }
  else{ std::cout << "Could not find file \"" << fileName << "\"" << std::endl; }
  
  fin.close();
} //SimParameters constructor

/******************************* ~SimParameters() (destructor) *******************************/
SimParameters::~SimParameters()
{
  if(TList_!=NULL)
  { delete TList_; }
  TList_ = NULL; 
}

/*********************************** Public Getter Methods: **********************************/
double       SimParameters::getTemperature    (uint i){ return TList_->at(i); }
uint         SimParameters::getNumWarmUpSweeps()      { return numWarmUpSweeps_; }
uint         SimParameters::getSweepsPerMeas  ()      { return sweepsPerMeas_; }
uint         SimParameters::getMeasPerBin     ()      { return measPerBin_; }
uint         SimParameters::getNumBins        ()      { return numBins_; }
std::string  SimParameters::getModelName      ()      { return modelName_; }

/****************************************** print() ******************************************/
void SimParameters::print()
{
  std::cout << "Simulation Parameters:\n"
            << "           Temperature List: [ ";
  
  //print the list of temperatures:
  for( uint i=0; i<(TList_->size() - 1); i++ )
  { std::cout << TList_->at(i) << ", "; }
  
  //print the last temperature element:
  if( TList_->size() > 0 )
  { std::cout << TList_->at(TList_->size() - 1); }
  std::cout << " ]\n";
  
  //print the rest of the parameters:
  std::cout << "                       Seed: " << seed_ << "\n"
            << "   Number of Warm-up Sweeps: " << numWarmUpSweeps_ << "\n"
            << "     Sweeps per Measurement: " << sweepsPerMeas_ << "\n"
            << "       Measurements per Bin: " << measPerBin_ << "\n"
            << "             Number of Bins: " << numBins_ << "\n"
            << "                 Model Name: " << modelName_ << "\n"
            << std::endl;
  
} //print method
