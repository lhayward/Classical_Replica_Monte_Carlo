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
        N2_ = N0_*(D_*(D_-1))/2;  //Number of plaquettes is N0_ * (D choose 2)
        plaqsPerSpin_ = 2*(D_-1);
        
        spins_ = new IsingSpins(alpha_, N1_);
        
        //create the plaqSpins_ and neighPlaqs_ arrays:
        plaqSpins_ = new uint*[N2_];
        for( uint i=0; i<N2_; i++ )
        { plaqSpins_[i] = new uint[SPINS_PER_PLAQ_]; }
        
        neighPlaqs_ = new uint*[N1_];
        for( uint i=0; i<N1_; i++ )
        { neighPlaqs_[i] = new uint[plaqsPerSpin_]; }
        
        //initialize the plaqSpins_ and neighPlaqs_ arrays:
        init_plaqArrays();
        
        //create and initialize the regionA_ array:
        regionA_ = new bool[N1_];
        init_regionA();
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
{
  if( spins_ != NULL )
  { delete spins_; }
  spins_ = NULL;
  
  //delete the plaqSpins_ array:
  for(uint i=0; i<N2_; i++)
  { 
    if( plaqSpins_[i] != NULL )
    { delete[] plaqSpins_[i]; }
    plaqSpins_[i] = NULL; 
  }
  if( plaqSpins_ != NULL )
  { delete[] plaqSpins_; }
  plaqSpins_ = NULL;
  
  //delete the neighPlaqs_ array:
  for(uint i=0; i<N1_; i++)
  { 
    if( neighPlaqs_[i] != NULL )
    { delete[] neighPlaqs_[i]; }
    neighPlaqs_[i] = NULL; 
  }
  if( neighPlaqs_ != NULL )
  { delete[] neighPlaqs_; }
  neighPlaqs_ = NULL;
  
}

/************************************* calculateEnergy() *************************************/
double ToricCode_1_q::calculateEnergy()
{
  double energy=0;
  
  return energy;
}

/************************************* init_plaqArrays() *************************************/
void ToricCode_1_q::init_plaqArrays()
{ 
  uint plaqNum=0; //counter for the plaquette number
  uint spin0, spin1, spin2, spin3;  //locations of the four spins on each plaquette
  
  //loop to calculate the four 1-cells associated with each plaquette:
  //loop over all 0-cells (vertices of the hypercube) first:
  for( uint zeroCell=0; zeroCell<N0_; zeroCell++ )
  {
    //loop over the (D choose 2) plaquettes associated to each 0-cell:
    for( uint i=0; i<(D_-1); i++ )
    {
      for( uint j=(i+1); j<D_; j++ )
      {
        spin0 = D_*zeroCell + i;
        spin1 = D_*zeroCell + j;
        spin2 = D_*hcube_->getNeighbour(zeroCell,j) + i;
        spin3 = D_*hcube_->getNeighbour(zeroCell,i) + j;
        
        plaqSpins_[plaqNum][0] = spin0;
        plaqSpins_[plaqNum][1] = spin1;
        plaqSpins_[plaqNum][2] = spin2;
        plaqSpins_[plaqNum][3] = spin3;
        
        neighPlaqs_[spin0][j-1]        = plaqNum;
        neighPlaqs_[spin1][i]          = plaqNum;
        neighPlaqs_[spin2][j-1 + D_-1] = plaqNum;
        neighPlaqs_[spin3][i + D_-1]   = plaqNum;
        
        plaqNum++;
        //plaqSpins_
      }
    }
  } //closes loop over 0-cells
}

/*************************************** init_regionA() **************************************/
void ToricCode_1_q::init_regionA()
{
  bool* cubeRegionA = hcube_->getRegionA(fracA_);
  
  //loop over all 0-cells (vertices of the hypercube):
  for( uint i=0; i<N0_; i++ )
  {
    //the D 1-cells associated with this 0-cell will be in region A iff the 0-cell is in 
    //region A:
    regionA_[D_*i]     = cubeRegionA[i];
    regionA_[D_*i + 1] = cubeRegionA[i];
    regionA_[D_*i + 2] = cubeRegionA[i];
  }
  
  if(cubeRegionA!=NULL)
  { delete[] cubeRegionA; }
  cubeRegionA = NULL; 
}

/*************************************** printParams() ***************************************/
void ToricCode_1_q::printParams()
{
  if( isValid_ )
  {
    std::cout << "(1," << (D_-1) << ") Toric Code Parameters:" << std::endl;
    Model::printParams();
    std::cout << "                Number of 0-cells = " << N0_ << "\n"
              << "                Number of 1-cells = " << N1_ << "\n"
              << "                Number of 2-cells = " << N2_ << "\n"
              << std::endl;
  }
  else
  {
    std::cout << "ERROR in ToricCode_1_q::printParams(): the ToricCode_1_q object is not "
              << "valid\n" << std::endl;
  }
}

/**************************************** printPlaqs() ***************************************/
void ToricCode_1_q::printPlaqs()
{
  std::cout << "Spins on Each Plaquette:" << std::endl;
  
  for( uint i=0; i<N2_; i++ )
  {
    std::cout << "  Plaquette " << i << ": [ ";
    for( uint j=0; j<SPINS_PER_PLAQ_; j++)
    { std::cout << plaqSpins_[i][j] << " "; }
    std::cout << "]\n";
  }
  std::cout << std::endl;
  
  std::cout << "Plaquettes Connected to Each Spin:" << std::endl;
  for( uint i=0; i<N1_; i++ )
  {
    std::cout << "  Spin " << i << ": [ ";
    for( uint j=0; j<plaqsPerSpin_; j++ )
    { std::cout << neighPlaqs_[i][j] << " "; }
    std::cout << "]\n";
  }
  std::cout << std::endl;
}

/**************************************** printSpins() ***************************************/
void ToricCode_1_q::printSpins()
{
  spins_->print();
  
  for(uint i=0; i<N1_; i++)
  { 
    std::cout.width(2);
    std::cout << regionA_[i] << " "; 
  }
  std::cout << std::endl;
}

/******************************** randomize(MTRand* randomGen) *******************************/
void ToricCode_1_q::randomize(MTRand* randomGen)
{
}

/************************************* singleSpinUpdate() ************************************/
void ToricCode_1_q::singleSpinUpdate()
{
}