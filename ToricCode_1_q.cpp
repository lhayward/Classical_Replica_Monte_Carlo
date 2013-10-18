/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   ToricCode_1_q.cpp
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include "FileReading.h"
#include "ToricCode_1_q.h"

/********* ToricCode_1_q(std::ifstream* fin, std::string fileName, Lattice* lattice) **********
**************************************** (constructor) ***************************************/
ToricCode_1_q::ToricCode_1_q(std::ifstream* fin, std::string fileName,
                                             Lattice* lattice)
  : Model(fin, fileName)
{
  if( isValid_ )  //check that parent is valid (read from file correctly)
  {
    if( lattice != NULL && lattice->isValid() )
    {
      hcube_ = dynamic_cast<Hypercube *>(lattice);
      if(hcube_)
      {
        D_  = hcube_->getD();
        N0_ = hcube_->getN();
        N1_ = D_*N0_;
        N2_ = (D_*(D_-1))/2*N0_;
        
        spins_ = new IsingSpins(alpha_, N1_);
      }
      else
      {
        std::cout << "ERROR in ToricCode_1_q constructor:\n" 
                  << "  A lattice of type Hypercube is required.\n"
                  << "  A lattice of type " << typeid(*lattice).name() << " was given.\n" 
                  << std::endl;
        isValid_ = false;
      }
    }
    else
    {
      std::cout << "ERROR in ToricCode_1_q constructor: The passed Lattice object is not "
                << "valid\n" << std::endl; 
      isValid_ = false;
    }
  } 
  else
  {
    std::cout << "ERROR in ToricCode_1_q constructor: the parent Model object is not valid\n"
              << std::endl;
  }
}

/******************************* ~ToricCode_1_q() (destructor) *******************************/
ToricCode_1_q::~ToricCode_1_q()
{ }

/************************************* calculateEnergy() *************************************/
double ToricCode_1_q::calculateEnergy()
{
  double energy=0;
  
  return energy;
}

/*************************************** printParams() ***************************************/
void ToricCode_1_q::printParams()
{
  if( isValid_ )
  {
    std::cout << "(1,D-1) Toric Code Parameters:" << std::endl;
    Model::printParams();
  }
  else
  {
    std::cout << "ERROR in ToricCode_1_q::printParams(): the ToricCode_1_q object is not "
              << "valid\n" << std::endl;
  }
}

/**************************************** printSpins() ***************************************/
void ToricCode_1_q::printSpins()
{
  spins_->print();
}

/******************************** randomize(MTRand* randomGen) *******************************/
void ToricCode_1_q::randomize(MTRand* randomGen)
{
}

/************************************* singleSpinUpdate() ************************************/
void ToricCode_1_q::singleSpinUpdate()
{
}