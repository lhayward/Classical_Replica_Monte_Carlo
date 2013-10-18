/**********************************************************************************************
******************************** CLASSICAL REPLICA MONTE CODE *********************************
***********************************************************************************************
* Lauren Hayward
***********************************************************************************************
* File:   ToricCode_q1_GeneralD.cpp
**********************************************************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include "FileReading.h"
#include "ToricCode_q1_GeneralD.h"

/************** ToricCode_q1_GeneralD(std::ifstream* fin, std::string fileName, ***************
********************************* ... Lattice* lattice) (constructor) ************************/
ToricCode_q1_GeneralD::ToricCode_q1_GeneralD(std::ifstream* fin, std::string fileName,
                                             Lattice* lattice)
  : Model(fin, fileName)
{
  if( isValid_ )  //check that parent is valid (read from file correctly)
  {
    if( lattice != NULL && lattice->isValid() )
    {
      lattice_ = dynamic_cast<Hypercube *>(lattice);
      if(!lattice_)
      {
        std::cout << "ERROR in ToricCode_q1_GeneralD constructor:\n" 
                  << "  A lattice of type Hypercube is required.\n"
                  << "  A lattice of type " << typeid(*lattice).name() << " was given.\n" 
                  << std::endl;
        isValid_ = false;
      }
    }
    else
    {
      std::cout << "ERROR in ToricCode_q1_GeneralD constructor: The passed Lattice object is "
                << "not valid\n" << std::endl; 
      isValid_ = false;
    }
  } 
  else
  {
    std::cout << "ERROR in ToricCode_q1_GeneralD constructor: the parent Model object is not "
              << "valid\n" << std::endl;
  }
}

/*************************** ~ToricCode_q1_GeneralD() (destructor) ***************************/
ToricCode_q1_GeneralD::~ToricCode_q1_GeneralD()
{  }

/************************************* calculateEnergy() *************************************/
double ToricCode_q1_GeneralD::calculateEnergy()
{
  double energy=0;
  
  return energy;
}

/****************************************** print() ******************************************/
void ToricCode_q1_GeneralD::print()
{
  if( isValid_ )
  {
    std::cout << "(1,D-1) Toric Code Parameters:" << std::endl;
    Model::print();
  }
  else
  {
    std::cout << "ERROR in ToricCode_q1_GeneralD::print(): the ToricCode_q1_GeneralD object " 
              << "is not valid\n" << std::endl;
  }
}

/******************************** randomize(MTRand* randomGen) *******************************/
void ToricCode_q1_GeneralD::randomize(MTRand* randomGen)
{

}

/************************************* singleSpinUpdate() ************************************/
void ToricCode_q1_GeneralD::singleSpinUpdate()
{
}