/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   ToricCode_q1_GeneralD.h
**********************************************************************************************/

#ifndef TORICCODE_H
#define TORICCODE_H

#include <string>
#include "Hypercube.h"
#include "IntegerSpins.h"
#include "Model.h"

class ToricCode_q1_GeneralD : public Model
{ 
  private:
    Hypercube* lattice_; //the hypercubic lattice on which the d.o.f. live
    
  public:
    //ToricCode_q1_GeneralD(std::ifstream* fin, Hypercube* lattice);
    ToricCode_q1_GeneralD(std::ifstream* fin, Lattice* lattice);
    virtual ~ToricCode_q1_GeneralD();
    
    virtual void print();
};

#endif  // TORICCODE_H
