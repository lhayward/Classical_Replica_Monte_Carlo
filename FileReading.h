/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   FileReading.h
**********************************************************************************************/

#ifndef FILE_READING_H
#define FILE_READING_H

#include <fstream>
#include <string>
#include <vector>

class FileReading 
{ 
  public:
    typedef unsigned int  uint;
    typedef unsigned long ulong;

    //methods to read from the passed input stream:
    static double               readDouble   (std::ifstream* fin, char delim);
    static uint                 readUint     (std::ifstream* fin, char delim); 
    static ulong                readLongInt  (std::ifstream* fin, char delim);
    static std::string          readString   (std::ifstream* fin, char delim);
    static std::vector<double>* readDoubleVec(std::ifstream* fin, char delim, char startChar, 
                                              char endChar);
};

#endif  // FILE_READING_H
