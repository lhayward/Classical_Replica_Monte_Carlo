/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   ToricCode_1_q.h
**********************************************************************************************/

#ifndef TORICCODE_1_Q_H
#define TORICCODE_1_Q_H

#include <string>
#include "Hypercube.h"
#include "IsingSpins.h"
#include "Model.h"

class ToricCode_1_q : public Model
{ 
  private:
    Hypercube* lattice_; //the hypercubic lattice on which the d.o.f. live
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    
  public:
    ToricCode_1_q(std::ifstream* fin, std::string fileName, Lattice* lattice);
    virtual ~ToricCode_1_q();
    
    virtual double calculateEnergy();
    virtual void print();
    virtual void randomize       (MTRand* randomGen);
    virtual void singleSpinUpdate();
};

#endif  // TORICCODE_1_Q_H
