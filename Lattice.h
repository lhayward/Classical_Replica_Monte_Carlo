/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   Lattice.h (Abstract Class)
**********************************************************************************************/

#ifndef LATTICE_H
#define LATTICE_H

class Lattice 
{ 
  public:
    typedef unsigned int  uint;
  
  protected: 
    uint   L_; //linear size of lattice
    uint   N_; //total number of lattice sites
    uint** neighbours_; //coordinates of each vertex's neighbours (no double counting)
    
  public:
    Lattice(uint L);
    Lattice(std::ifstream* fin);
    virtual ~Lattice();
    
    //pure virtual method:
    virtual void print() = 0;
    //virtual uint getNeighbour(uint i, uint j) = 0;
};

#endif  // LATTICE_H
