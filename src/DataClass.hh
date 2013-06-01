#ifndef DATACLASS_h
#define DATACLASS_h 

using namespace std;

#include <iostream>
#include <iomanip>

Class DataClass
{
 public:
  
  DataClass( int photonCount = 0, double time = 0.0, double energy = 0.0)
    {
      TotalPhoton = photonCount;
      TotalTime = time;
      TotalEnergy = energy;
