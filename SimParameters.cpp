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
    numWarmUpSweeps_ = readInt    (&fin, EQUALS_CHAR);
    sweepsPerMeas_   = readInt    (&fin, EQUALS_CHAR);
    measPerBin_      = readInt    (&fin, EQUALS_CHAR);
    numBins_         = readInt    (&fin, EQUALS_CHAR);
  }
  else{ std::cout << "Could not find file \"" << fileName << "\"" << std::endl; }
  
  fin.close();
} //SimParameters constructor

/******************************* ~SimParameters() (destructor) *******************************/
SimParameters::~SimParameters()
{ }

/************************ readDouble(std::ifstream* fin, char delim) *************************/
double SimParameters::readDouble(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtod( (currLine.substr(index+1)).c_str(), NULL);
} //readDouble method

/************************** readInt(std::ifstream* fin, char delim) **************************/
uint SimParameters::readInt(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtol( (currLine.substr(index+1)).c_str(), NULL, 0);
} //readInt method

/************************ readLongInt(std::ifstream* fin, char delim) ************************/
ulong SimParameters::readLongInt(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtoul( (currLine.substr(index+1)).c_str(), NULL, 0);
} //readLongInt method

/********** readTList(std::ifstream* fin, char delim, char startChar, char endChar) ***********
* This method gets the next line from the passed fin and parses it as a list of doubles, which
* it stores as the temperatures in the TList_ vector.
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

/****************************************** print() ******************************************/
void SimParameters::print()
{
} //print method
