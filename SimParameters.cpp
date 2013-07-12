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
    readTList                     (&fin, EQUALS_CHAR, LIST_START_CHAR, LIST_END_CHAR);
    seed_            = readLongInt(&fin, EQUALS_CHAR);
    numWarmUpSweeps_ = readUint   (&fin, EQUALS_CHAR);
    sweepsPerMeas_   = readUint   (&fin, EQUALS_CHAR);
    measPerBin_      = readUint   (&fin, EQUALS_CHAR);
    numBins_         = readUint   (&fin, EQUALS_CHAR);
    modelName_       = readString (&fin, EQUALS_CHAR);
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

/************************* readDouble(std::ifstream* fin, char delim) *************************
* Private method 
*
* This method reads in and parses a double from the given input stream.
**********************************************************************************************/
double SimParameters::readDouble(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtod( (currLine.substr(index+1)).c_str(), NULL);
} //readDouble method

/************************** readUint(std::ifstream* fin, char delim) **************************
* Private method 
*
* This method reads in and parses an unsigned integer from the given input stream.
**********************************************************************************************/
uint SimParameters::readUint(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtol( (currLine.substr(index+1)).c_str(), NULL, 0);
} //readUint method

/************************ readLongInt(std::ifstream* fin, char delim) *************************
* Private method 
*
* This method reads in and parses an unsigned long integer from the given input stream.
**********************************************************************************************/
ulong SimParameters::readLongInt(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtoul( (currLine.substr(index+1)).c_str(), NULL, 0);
} //readLongInt method

/************************* readString(std::ifstream* fin, char delim) *************************
* Private method 
*
* This method reads in a string from the given input stream.
**********************************************************************************************/
std::string SimParameters::readString(std::ifstream* fin, char delim)
{
  std::string currLine;
  std::string result;
  uint        index;
  
  //cut off the part of the line up to and including the delim character:
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  currLine = currLine.substr(index+1);
  
  //trim the leading whitespace:
  index = currLine.find_first_not_of(" \t\n");
  currLine = currLine.substr(index);
  
  //trim the trailing whitespace:
  index = currLine.find_last_not_of(" \t\n");
  currLine = currLine.substr(0,index+1);
  
  return currLine;
}

/********** readTList(std::ifstream* fin, char delim, char startChar, char endChar) ***********
* Private method
*
* This method reads in and parses a list of doubles from the given input stream. It stores this
* list as the temperatures in the TList_ vector.
**********************************************************************************************/
void SimParameters::readTList(std::ifstream* fin, char delim, char startChar, char endChar)
{
  std::string currLine;
  uint        delimIndex, startIndex, endIndex, commaIndex;
  
  //cut off the part of the line up to and including the delim character:
  getline(*fin, currLine);
  delimIndex = currLine.find_last_of(delim);
  currLine = currLine.substr(delimIndex+1);
  
  //cut off the characters that indicate the start and end of the list:
  startIndex = currLine.find_first_of(startChar);
  endIndex = currLine.find_last_of(endChar);
  currLine = currLine.substr(startIndex+1, (endIndex - startIndex - 1) );
  
  //read in the doubles in the list and store them in TList_:
  commaIndex = currLine.find_first_of(",");
  while( commaIndex<currLine.size() )
  {
    TList_->push_back( strtod( (currLine.substr(0, commaIndex)).c_str(), NULL) );
    currLine = currLine.substr(commaIndex+1);
    commaIndex = currLine.find_first_of(",");
  }
  TList_->push_back( strtod( currLine.c_str(), NULL) );
} //readTList method
