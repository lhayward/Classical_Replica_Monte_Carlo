/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Model.h (Abstract Class)
**********************************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "MersenneTwister.h"

class Model 
{ 
   public:
    typedef unsigned int  uint;
    
  protected:
    bool          isValid_; //whether or not this is a valid Model object
    double        J_;       //coupling 
    uint          alpha_;   //the number of replicas
    double        fracA_;   //the fractions of spins in region A (only relevant for alpha_>=2)
    double        T_;       //current temperature
    bool*         regionA_; //indicates whether or not each spin is in region A
    
  public:
    Model(std::ifstream* fin, std::string fileName);
    virtual ~Model();
    
    //methods that can be overwritten by child classes:
    virtual void printParams();
    virtual void setT (double newT);
    
    //pure virtual methods (to be implemented by all child classes):
    virtual double calculateEnergy() = 0;
    virtual void   printRegionA   () = 0;
    virtual void   printSpins     () = 0;
    virtual void   randomize      (MTRand* randomGen) = 0;
    virtual void   sweep          (MTRand* randomGen) = 0;
};

#endif  // MODEL_H
