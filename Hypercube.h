/*********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE ********************************
**********************************************************************************************
* Lauren Hayward
**********************************************************************************************
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
*********************************************************************************************/

#ifndef HYPERCUBE_H 
#define HYPERCUBE_H

#include "Lattice.h"

class Hypercube: public Lattice
{ 
  private:
    int   D_; //dimension
    
    int intPower(int base, int exp);
    
  public:
    Hypercube(int L, int D);
    virtual ~Hypercube();
    
    void print();
};

#endif  // HYPERCUBE_H
