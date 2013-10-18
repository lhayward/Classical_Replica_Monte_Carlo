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
  public:
    typedef unsigned int  uint;
    
  private:
    uint        D_;   //dimension
    uint        N0_;  //number of 0-cells (vertices)
    uint        N1_;  //number of 1-cells (bonds), i.e. the number of d.o.f. since the spins
                      //live on the bonds
    uint        N2_;  //number of 2-cells (plaquettes)
    Hypercube*  hcube_; //the hypercubic lattice on which the d.o.f. live
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    
  public:
    ToricCode_1_q(std::ifstream* fin, std::string fileName, Lattice* lattice);
    virtual ~ToricCode_1_q();
    
    virtual double calculateEnergy ();
    virtual void   printParams     ();
    virtual void   printSpins      ();
    virtual void   randomize       (MTRand* randomGen);
    virtual void   singleSpinUpdate();
};  

#endif  // TORICCODE_1_Q_H
