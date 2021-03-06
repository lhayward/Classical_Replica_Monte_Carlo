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
    
    bool        measureWilsonLoops_;  //whether or not the Wilson loops should be written the
                                      //bin file
    uint        D_;   //dimension
    uint        L_;   //hypercube linear length
    uint        N0_;  //number of 0-cells (vertices)
    uint        N1_;  //number of 1-cells (bonds), i.e. the number of d.o.f. since the spins
                      //live on the bonds
    uint        N2_;  //number of 2-cells (plaquettes)
    
    uint        numProbs_; //number of elements in the singleUpdateProbs array
    double*     localUpdateProbs_; //the exponentials needed for the single-spin updates 
                                   //(pre-computed to save time)
    uint        plaqsPerSpin_;  //number of plaquettes touching each spin
    Hypercube*  hcube_; //the hypercubic lattice on which the d.o.f. live
    IsingSpins* spins_; //the degrees of freedom (d.o.f.) for the model
    uint**      plaqSpins_; //plaqSpins_[i] stores the indices of the spins touching
                            //plaquette i
    uint**      neighPlaqs_;  //neighPlaqs_[i] stores the indices of the 2(D-1) plaquettes
                              //touching spin i
    int**       plaqProds_; //plaqProds_[a][i] stores the product of all spins on plaquette i
                            //in replica a
    
    void   init_plaqArrays   ();
    void   init_regionA      ();
    void   localUpdate       (MTRand* randomGen);
    void   printPlaqProds    ();
    void   printPlaqs        ();
    uint   uintPower(uint base, uint exp);
    void   updateAllPlaqProds();
    double wilsonLoop        (uint dir); //driver method for calculating the average Wilson loop
                                        //in the lattice direction "dir" (0 <= dir <= D_-1)
    int    wilsonLoop_rec    (uint wilsonDir, int latticeDir, uint x[], int WSum);
                                        //recursive method to be used with the above 
                                        //wilsonLoop driver method
    
  public:
    ToricCode_1_q(std::ifstream* fin, std::string outFileName, Lattice* lattice);
    virtual ~ToricCode_1_q();
    
    virtual void makeMeasurement();
    virtual void printParams    ();
    virtual void printRegionA   ();
    virtual void printSpins     ();
    virtual void randomize      (MTRand* randomGen);
    virtual void setT           (double newT);
    virtual void sweep          (MTRand* randomGen);
    virtual void updateEnergy   ();
    virtual void writeBin       (int binNum, int numMeas);
};  

#endif  // TORICCODE_1_Q_H
