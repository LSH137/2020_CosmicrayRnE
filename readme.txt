This repository is for sharing the source code which writed to do Cosmic ray R&E.

1. Graph_Observed
  this directory have root macro file for drawing observed data:time graph.
  Constant.h : some constants like dir or number of maximum file number.
  ObservedGraph.C : root macro for drawing graph.
  
2. Graph_Observedflux_Ratio
  this directory have root macro file for drawing cosmic-ray flux by SFU.
  Constant.h : same purpose with upper one. (some constants like dir or number of maximum file number.)
  Result.C : root macro for drawing graph.
  regulate.cpp : change the form of my cosmicray data.
  
3. Graph_RadioData
  FoF2_HmF2.C : draw Fof2 by time and draw HmF2 by time. This macro make 2 graph.
  magich.C : draw magich dy time.
  sfu.C : draw sfu by time.
  
4. Graph_SimulationData
  AdvencedSimulation.C : draw histogram and get excess / total and draw graph excess/total by energy
                          we simulate electron, muon and proton for 0.1MeV ~ 20MeV with interver 0.1MeV. this file read simulation data file and draw three graph(mu, e, proton) on one canvas.
  Constant.h : same purpose with upper one.
  
5. program
    5.1 Advenced_G4Make: make Geant4 project. we need to simulate many kinds of energy. Actually, we can realize with geant4 macro file but we need to calculate fast. So we make eatch project for eatch energy and run at once. (Use GeV unit)
    5.2 Advenced_LowEnergy_G4Make: same purpose with 5.1 but this project make simulation for lower energy. (use MeV unit)
    5.3 AdvencedProcess : Source codes for raw data process. raw data is dE/dt and we get total energy depositon with this program.
    5.4 autorun_cosmicrayCOM : autorun Geant4 simulation which made by Advenced_G4Make or Advenced_LowEnergy_G4Make.
    5.5 autorun_myLaptop : autorun Geant4 simulation which made by Advenced_G4Make or Advenced_LowEnergy_G4Make.
    5.6 OldVersionProess: Source code which used previous cosmic ray research.
 
6. Geant4_sample
  sample project. other Geant4 projects are all same except energy and type of particle(mu, e, proton)
