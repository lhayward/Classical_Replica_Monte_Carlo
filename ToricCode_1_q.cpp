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

/******** ToricCode_1_q(std::ifstream* fin, std::string outFileName, Lattice* lattice) ********
**************************************** (constructor) ***************************************/
ToricCode_1_q::ToricCode_1_q(std::ifstream* fin, std::string outFileName, Lattice* lattice)
  : Model(fin, outFileName)
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
        
        //create the localUpdateProbs_ array:
        numProbs_ = (D_-1)*alpha_;
        localUpdateProbs_ = new double[numProbs_];
        for( uint i=0; i<numProbs_; i++ )
        { localUpdateProbs_[i] = 0; }
        
        //create and initialize the plaqProds_ array:
        plaqProds_ = new int*[alpha_];
        for( uint a=0; a<alpha_; a++ )
        { plaqProds_[a] = new int[N2_]; }
        updateAllPlaqProds(); //initialize the plaqProds_ array and energy_ based on the
                              //current spin configuration
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

/******************************* localUpdate(MTRand* randomGen) ******************************/
void ToricCode_1_q::localUpdate(MTRand* randomGen)
{
  uint latticeSite; //randomly selected spin location
  uint replicaStart; //replica where the attempted local update starts
  uint replicaEnd;   //replica where the attempted local update ends
  int  nnPlaqSum;   //sum of the plaquette products on the plaquettes neighbouring latticeSite
  
  latticeSite = randomGen->randInt(N1_-1);
  
  //if the spin is in region A, we must consider flipping spins in all replicas: 
  if( regionA_[latticeSite] )
  {
    replicaStart = 0;
    replicaEnd   = alpha_ - 1;
  }
  //if the spin is in region B, we must choose one replica in which to attempt the update:
  else
  { 
    replicaStart = randomGen->randInt(alpha_-1); 
    replicaEnd   = replicaStart;
  }
  
  //loop to calculate the sum for the energy difference:
  nnPlaqSum=0;
  for( uint a=replicaStart; a<=replicaEnd; a++ )
  {
    for( uint i=0; i<plaqsPerSpin_; i++ )
    { nnPlaqSum += plaqProds_[a][ neighPlaqs_[latticeSite][i] ]; }
  }
  
  //check if we will flip the spin:
  if( (J_*nnPlaqSum <= 0) || 
      (randomGen->randDblExc() < localUpdateProbs_[(abs(nnPlaqSum)/2)-1]) )
  {
    //flip the spin:
    spins_->flip(latticeSite, replicaStart, replicaEnd);
    
    //update the plaqProds_ array:
    for( uint a=replicaStart; a<=replicaEnd; a++ )
    {
      for( uint i=0; i<plaqsPerSpin_; i++ )
      { plaqProds_[a][ neighPlaqs_[latticeSite][i] ] *= -1; }
    }
    
    //update the energy:
    energy_ += 2*J_*nnPlaqSum;
  } //if
}

/*************************************** printParams() ***************************************/
void ToricCode_1_q::printParams()
{
  if( isValid_ )
  {
    std::cout << "(1," << (D_-1) << ") Toric Code Parameters:\n"
              << "---------------------------" << std::endl;
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

/************************************** printPlaqProds() *************************************/
void ToricCode_1_q::printPlaqProds()
{
  std::cout << "Plaquette Products:\n";
  for(uint a=0; a<alpha_; a++)
  {
    std::cout << "  Replica #" << (a+1) << ":" << std::endl;
    for(uint i=0; i<N2_; i++)
    { 
      std::cout.width(2);
      std::cout << plaqProds_[a][i] << " "; 
    }
    std::cout << std::endl;
  } //a
  std::cout << std::endl;
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

/*************************************** printRegionA() **************************************/
void ToricCode_1_q::printRegionA()
{
  std::cout << "Region A:\n";
  for( uint i=0; i<N1_; i++ )
  { 
    std::cout.width(2);
    std::cout << regionA_[i] << " "; 
  }
  std::cout << "\n" << std::endl;
}

/**************************************** printSpins() ***************************************/
void ToricCode_1_q::printSpins()
{
  spins_->print();
}

/******************************** randomize(MTRand* randomGen) *******************************/
void ToricCode_1_q::randomize(MTRand* randomGen)
{
  spins_->randomize(randomGen, regionA_);
  updateAllPlaqProds();
}

/************************************* setT(double newT) *************************************/
void ToricCode_1_q::setT(double newT)
{ 
  Model::setT(newT); 

  //update the localUpdateProbs_ array:
  for( uint i=0; i<numProbs_; i++ )
  { localUpdateProbs_[i] = exp(-abs(J_)*2*(2*(i+1))/T_); }
}

/********************************** sweep(MTRand* randomGen) *********************************/
void ToricCode_1_q::sweep(MTRand* randomGen)
{
  uint numSpins = alpha_*N1_;
  
  for( uint i=0; i<numSpins; i++ )
  { localUpdate(randomGen); }
}

/************************************ updateAllPlaqProds() ***********************************/
void ToricCode_1_q::updateAllPlaqProds()
{
  //loop over replicas:
  for( uint a=0; a<alpha_; a++ )
  {
    //loop over plaquettes:
    for( uint i=0; i<N2_; i++ )
    {
      plaqProds_[a][i] = 1;
      //loop over the spins on this plaquette:
      for( uint j=0; j<SPINS_PER_PLAQ_; j++ )
      { plaqProds_[a][i] *= spins_->getSpin(a, plaqSpins_[i][j]); }
    }
  } //loop over replicas
  updateEnergy();
}

/*************************************** updateEnergy() **************************************/
void ToricCode_1_q::updateEnergy()
{
  energy_=0;
  for( uint a=0; a<alpha_; a++ )
  {
    for( uint i=0; i<N2_; i++ )
    { energy_ += plaqProds_[a][i]; }
  }
  energy_ *= -J_;
}

/***************************** writeBin(int binNum, int numMeas) *****************************/
void ToricCode_1_q::writeBin(int binNum, int numMeas)
{
  fout << hcube_->getL() << '\t' << T_ << '\t' << binNum;
}