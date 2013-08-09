/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   IsingModel.h
**********************************************************************************************/

#ifndef ISINGMODEL_H
#define ISINGMODEL_H

#include <string>
#include "Hypercube.h"
#include "IsingSpins.h"
#include "Model.h"

class IsingModel : public Model
{ 
  private:
    Lattice* lattice_; //the lattice on which the d.o.f. live
    Lattice* spins_; //the degrees of freedom (d.o.f.) for the model
    
  public:
    IsingModel(std::ifstream* fin, Lattice* lattice);
    virtual ~IsingModel();
    
    virtual double calculateEnergy();
    virtual void   print();
    virtual void   singleSpinUpdate();
};

#endif  // ISINGMODEL_H
