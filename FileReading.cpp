/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   FileReading.cpp
**********************************************************************************************/

#include <fstream>
#include <string>
#include <vector>
#include "FileReading.h"

//typdefs needed because uint and ulong are return types:
typedef FileReading::uint  uint;
typedef FileReading::ulong ulong; 

/************************* readDouble(std::ifstream* fin, char delim) *************************
* This method reads in and parses a double from the given input stream.
**********************************************************************************************/
double FileReading::readDouble(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtod( (currLine.substr(index+1)).c_str(), NULL);
} //readDouble method

/************************** readUint(std::ifstream* fin, char delim) **************************
* This method reads in and parses an unsigned integer from the given input stream.
**********************************************************************************************/
uint FileReading::readUint(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtol( (currLine.substr(index+1)).c_str(), NULL, 0);
} //readUint method

/************************ readLongInt(std::ifstream* fin, char delim) *************************
* This method reads in and parses an unsigned long integer from the given input stream.
**********************************************************************************************/
ulong FileReading::readLongInt(std::ifstream* fin, char delim)
{
  std::string currLine;
  uint index;
  
  getline(*fin, currLine);
  index = currLine.find_last_of(delim);
  return strtoul( (currLine.substr(index+1)).c_str(), NULL, 0);
} //readLongInt method

/************************* readString(std::ifstream* fin, char delim) *************************
* This method reads in a string from the given input stream.
**********************************************************************************************/
std::string FileReading::readString(std::ifstream* fin, char delim)
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
  result = currLine.substr(0,index+1);
  
  return result;
}

/******** readDoubleVec(std::ifstream* fin, char delim, char startChar, char endChar); ********
* This method reads in and parses a vector of doubles from the given input stream.
**********************************************************************************************/
std::vector<double>* FileReading::readDoubleVec(std::ifstream* fin, char delim, 
                                                  char startChar, char endChar)
{
  std::vector<double>* result = new std::vector<double>;
  std::string          currLine;
  uint                 delimIndex;
  uint                 startIndex;
  uint                 endIndex;
  uint                 commaIndex;
  
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
    result->push_back( strtod( (currLine.substr(0, commaIndex)).c_str(), NULL) );
    currLine = currLine.substr(commaIndex+1);
    commaIndex = currLine.find_first_of(",");
  }
  result->push_back( strtod( currLine.c_str(), NULL) );
  
  return result;
} //readDoubleVec method