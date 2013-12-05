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
    
    void accumulate(std::string label, double newMeas);
    void insert    (std::string label);
    void print     ();
    void zero      ();
};

#endif  // MEASURE_H
