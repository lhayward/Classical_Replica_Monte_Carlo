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
#include "IsingSpins.h"
#include "Model.h"

class ToricCode_q1_GeneralD : public Model
{ 
  private:
    Hypercube* lattice_; //the hypercubic lattice on which the d.o.f. live
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    
  public:
    ToricCode_q1_GeneralD(std::ifstream* fin, Lattice* lattice);
    virtual ~ToricCode_q1_GeneralD();
    
    virtual double calculateEnergy();
    virtual void print();
    virtual void randomize       (MTRand* randomGen);
    virtual void singleSpinUpdate();
};

#endif  // TORICCODE_H
