/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Hypercube.h
* Description: The vertices of a are labelled along the x-direction, followed by the 
*              y-direction, etc. 
*              So for example, the first L^2 vertices (in the x-y plane in D>=2) are:
*                   (L^2-L)  (L^2-L+1)  . . .  (L^2-1)
*                      .         .                .
*                      .         .                .
*                      .         .                .
*                      L        L+1     . . .    2L-1
*                      0         1      . . .    L-1
**********************************************************************************************/

#ifndef HYPERCUBE_H 
#define HYPERCUBE_H

#include <fstream>
#include "Lattice.h"

class Hypercube : public Lattice
{ 
  public:
    typedef unsigned int  uint;
    
  private:
    uint   D_; //dimension
    
    uint uintPower(uint base, uint exp);
    void initNAndNeighbours();
    
  public:
    Hypercube(uint L, uint D);
    Hypercube(std::ifstream* fin);
    virtual ~Hypercube();
    
    virtual void print();
    
    //getter methods:
    uint getD();
};

#endif  // HYPERCUBE_H
