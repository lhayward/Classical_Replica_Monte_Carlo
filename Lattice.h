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
    uint   z_; //number of nearest neighbouring sites for each site
    uint** neighbours_; //coordinates of each vertex's neighbours (no double counting)
    
  public:
    Lattice(uint L);
    Lattice(std::ifstream* fin);
    virtual ~Lattice();
    
    //pure virtual method:
    virtual void print() = 0;
    //virtual uint getNeighbour(uint i, uint j) = 0;
    
    //getter methods:
    uint getN();
    uint getZ();
};

#endif  // LATTICE_H
