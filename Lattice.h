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
  protected: 
    int   L_; //linear size of lattice
    int   N_; //total number of lattice sites
    int** neighbours_; //coordinates of each vertex's neighbours (no double counting)
    
  public:
    Lattice(int L);
    Lattice(std::ifstream* fin);
    virtual ~Lattice();
    
    //pure virtual method:
    virtual void print() = 0;
};

#endif  // LATTICE_H
