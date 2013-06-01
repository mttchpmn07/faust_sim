#ifndef ExN01PrimaryGeneratorAction_h
#define ExN01PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class ExN01PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ExN01PrimaryGeneratorAction();
    ~ExN01PrimaryGeneratorAction();

  public:
    void generatePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;
};

#endif

#include "ExN01PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Geantino.hh"
#include "globals.hh"

ExN01PrimaryGeneratorAction::ExN01PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  particleGun->SetParticleDefinition(G4Geantino::GeantinoDefinition());
  particleGun->SetParticleEnergy(1.0*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(-2.0*m,0.0*m,0.0*m));
}

ExN01PrimaryGeneratorAction::~ExN01PrimaryGeneratorAction()
{
  delete particleGun;
}

void ExN01PrimaryGeneratorAction::generatePrimaries(G4Event* anEvent)
{
  G4int i = anEvent->get_eventID() % 3;
  switch(i)
  {
    case 0:
      particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.0));
      break;
    case 1:
      particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.1,0.0));
      break;
    case 2:
      particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.1));
      break;
  }

  particleGun->generatePrimaryVertex(anEvent);
}
