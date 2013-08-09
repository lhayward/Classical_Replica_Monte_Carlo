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

class Model 
{ 
  protected:
    double        J_;     //coupling 
    int           alpha_; //the number of replicas
    double        fracA_; //the fractions of spins in region A (only relevant for alpha_ >= 2)
    
  public:
    Model(std::ifstream* fin);
    virtual ~Model();
    
    virtual double calculateEnergy() = 0;
    virtual void   print() = 0;
    virtual void   singleSpinUpdate() = 0;
};

#endif  // MODEL_H
