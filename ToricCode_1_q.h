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
    static const uint  SPINS_PER_PLAQ_=4;
    
    uint        D_;   //dimension
    uint        N0_;  //number of 0-cells (vertices)
    uint        N1_;  //number of 1-cells (bonds), i.e. the number of d.o.f. since the spins
                      //live on the bonds
    uint        N2_;  //number of 2-cells (plaquettes)
    
    uint        numProbs_; //number of elements in the singleUpdateProbs array
    double*     singleUpdateProbs_; //the exponentials needed for the single-spin updates 
                                    //(pre-computed to save time)
    uint        plaqsPerSpin_;  //number of plaquettes touching each spin
    Hypercube*  hcube_; //the hypercubic lattice on which the d.o.f. live
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    uint**      plaqSpins_; //plaqSpins_[i] stores the indices of the spins touching
                            //plaquette i
    uint**      neighPlaqs_;  //neighPlaqs_[i] stores the indices of the 2(D-1) plaquettes
                              //touching spin i
    
    void init_plaqArrays();
    void init_regionA   ();
    void printPlaqs     ();
    
    
  public:
    ToricCode_1_q(std::ifstream* fin, std::string fileName, Lattice* lattice);
    virtual ~ToricCode_1_q();
    
    virtual double calculateEnergy();
    virtual void   printParams    ();
    virtual void   printRegionA   ();
    virtual void   printSpins     ();
    virtual void   randomize      (MTRand* randomGen);
    virtual void   setT           (double newT);
    virtual void   sweep          ();
};  

#endif  // TORICCODE_1_Q_H
