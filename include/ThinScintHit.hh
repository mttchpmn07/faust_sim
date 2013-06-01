//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#ifndef ThinScintHit_h
#define ThinScintHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class G4AttDef;

class ThinScintHit : public G4VHit
{
  public:

      ThinScintHit();
      ~ThinScintHit();
      ThinScintHit(const ThinScintHit &right);
      const ThinScintHit& operator=(const ThinScintHit &right);
      G4int operator==(const ThinScintHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      void Print();

  private:
  // G4double edep;
      G4ThreeVector pos;
     
  public:
      // inline void SetEdep(G4double de)
      // { edep = de; }
      // inline G4double GetEdep()
      // { return edep; }
      inline void SetPos(G4ThreeVector xyz)
      { pos = xyz; }
      inline G4ThreeVector GetPos()
      { return pos; }

};

typedef G4THitsCollection<ThinScintHit> ThinScintHitsCollection;

extern G4Allocator<ThinScintHit> ThinScintHitAllocator;

inline void* ThinScintHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) ThinScintHitAllocator.MallocSingle();
  return aHit;
}

inline void ThinScintHit::operator delete(void *aHit)
{
  ThinScintHitAllocator.FreeSingle((ThinScintHit*) aHit);
}

#endif
