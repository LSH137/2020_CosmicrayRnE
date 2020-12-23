DetectorConstruction.cc : make geometry of simulation.
Hit.cc : if you make sensitive detector, you need to make source code for hit.
PrimaryGeneratorAction.cc : you can set which particle, energy, shoot direction to simulate
RunAction.cc : set which data to collect and how to save it.
SensitiveDetector.cc : source for sensitive detector. collect data at here.
SteppingAction.cc : I don't know why this file need. 


I refer internet page for make this project.
https://scicomex.com/geant4-sensitive-detector-and-hits/
https://www.opentutorials.org/module/2275/13646
(last access date: 2020-12-23)

and geant4 example which provided when install geant4.
