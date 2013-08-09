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
    double        T_;     //current temperature
    
  public:
    Model(std::ifstream* fin);
    virtual ~Model();
    
    //methods that can be overwritten by child classes:
    virtual void print();
    virtual void setT (double newT);
    
    //pure virtual methods (to be implemented by all child classes):
    virtual double calculateEnergy () = 0;
    virtual void   singleSpinUpdate() = 0;
};

#endif  // MODEL_H
