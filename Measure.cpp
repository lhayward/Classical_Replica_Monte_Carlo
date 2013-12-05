/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Measure.cpp (Abstract Class)
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include "Measure.h"

/********************************** Measure() (constructor) **********************************/
Measure::Measure()
{ }

/********************************** ~Measure() (destructor) **********************************/
Measure::~Measure()
{ }

/*********************** accumulate(std::string label, double newMeas) ***********************/
void Measure::accumulate(std::string label, double newMeas)
{ measurements[label] += newMeas; }

/********************************* insert(std::string label) *********************************/
void Measure::insert(std::string label)
{ measurements.insert( std::pair<std::string,double>(label, 0.0) ); }

/****************************************** print() ******************************************/
void Measure::print()
{
  std::map<std::string,double>::iterator it;
  
  std::cout << "Measurements:" << std::endl;
  for( it=measurements.begin(); it!=measurements.end(); ++it )
  { std::cout << "  " << it->first << ": " << it->second << '\n'; }
  std::cout << std::endl;
}

/******************************************* zero() ******************************************/
void Measure::zero()
{
  std::map<std::string,double>::iterator it;
  
  for( it=measurements.begin(); it!=measurements.end(); ++it )
  { it->second = 0.0; }
}