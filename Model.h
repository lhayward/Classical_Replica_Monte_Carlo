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
#include "IntegerSpins.h"

class Model 
{ 
  protected:
    double        J_;     //coupling 
    int           alpha_; //the number of replicas
    double        fracA_; //the fractions of spins in region A (only relevant for alpha_ >= 2)
    IntegerSpins* spins_; //the degrees of freedom for the model
    
  public:
    Model(std::ifstream* fin);
    virtual ~Model();
    
    void print();
};

#endif  // MODEL_H
