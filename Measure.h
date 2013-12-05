/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Measure.h
**********************************************************************************************/

#ifndef MEASURE_H
#define MEASURE_H

#include <map>
#include <string>

class Measure 
{ 
   private:
    std::map<std::string,double> measurements;
    
  public:
    Measure();
    virtual ~Measure();
};

#endif  // MEASURE_H
