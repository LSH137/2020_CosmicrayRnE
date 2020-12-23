#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "SensitiveDetector.hh"

// unit define
// length: meter *m
// tempreature: degree

#define labTemp 273 //0 celcious degree

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{

}

DetectorConstruction::~DetectorConstruction()
{

}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4double GapBetweenScintillator = 0.16*m;
  G4double GapBetweenScintillatorAndFloor = 0.4*m;
  G4double WorldSize = 4.0*m;
  G4double Detector_size_xy = 1.0*m;
  G4double Detector_size_z = 0.015*m;
  G4double Detector_offset_z = 0.05*m;
  G4double IronCaseThickness = 0.001*m;
  G4double Floor_size_xy = 2.0*m;
  G4double Floor_size_z = 0.5*m;
  G4double Roof_size_xy = 2.0*m;
  G4double Roof_size_z = 0.002*m;
  G4double Roof_angle = 27.0*deg;

  G4NistManager* nist = G4NistManager::Instance();

 
    /* create a new sensitive detector called "SD_1" */
    SensitiveDetector* sensitiveDet = new SensitiveDetector("SD_1");
    SensitiveDetector* sensitiveDet2 = new SensitiveDetector("SD_2");
 
    /* register the sensitive detector with the manager */
    G4SDManager::GetSDMpointer()-> AddNewDetector(sensitiveDet);
    G4SDManager::GetSDMpointer()-> AddNewDetector(sensitiveDet2);

    //World
    /*
        World is made of G4_Air
        size is 4m * 4m * 4m (x, y, z)
        copy number 0
    */
   G4Material* world_mat = nist -> FindOrBuildMaterial("G4_AIR");
   //G4double world_size = 4000*mm;

   G4Box* solidWorld =
    new G4Box("World",
                0.5 * WorldSize,
                0.5 * WorldSize,
                0.5 * WorldSize);
    
    G4LogicalVolume* logicWorld = 
      new G4LogicalVolume(solidWorld, 
                          world_mat,
                          "World");

    G4VPhysicalVolume* physWorld = 
      new G4PVPlacement(0, 
                        G4ThreeVector(),
                        logicWorld, 
                        "World", 
                        0, 
                        false, 
                        0, 
                        true);

    //Detector
    /*
        Detector is made of C8H8
        size is 1m * 1m * 1.6cm
                    copy number
        Detector1 :        1
        Detector2 :        2
    */
   G4Element* Carbon = new G4Element("carbon", "C", 6, 12.011*g/mole);
   G4Element* Hydrogen = new G4Element("hydrogen", "H", 1, 1.00794*g/mole);

   G4Material* detector_mat = new G4Material("scintillator", 0.909*g/cm3, 2, kStateSolid, labTemp);

   detector_mat -> AddElement(Carbon, 8);
   detector_mat -> AddElement(Hydrogen, 8);

   //front scintillator
   G4Box* solidDetector = 
    new G4Box("Detector",
               Detector_size_xy * 0.5, 
               Detector_size_xy * 0.5, 
               Detector_size_z * 0.5);

   G4LogicalVolume* logicDetector = 
    new G4LogicalVolume(solidDetector, 
                        detector_mat,
                        "Detector");

    new G4PVPlacement(0,
                      G4ThreeVector(0, 0, Detector_offset_z),
                      logicDetector,
                      "Detector",
                      logicWorld,
                      false,
                      1,
                      true);

    SetSensitiveDetector("Detector", sensitiveDet);

    //second scintillator
    G4Box* solidDetector2 =
      new G4Box("Detector2",
                 Detector_size_xy * 0.5,
                 Detector_size_xy * 0.5,
                 Detector_size_z * 0.5);
    
    G4LogicalVolume* logicDetector2 =
      new G4LogicalVolume(solidDetector2,
                          detector_mat,
                          "Detector2");
      
      new G4PVPlacement(0,
                        G4ThreeVector(0, 0, Detector_offset_z + GapBetweenScintillator),
                        logicDetector2,
                        "Detector2",
                        logicWorld,
                        false,
                        2,
                        true);

    SetSensitiveDetector("Detector2", sensitiveDet2);

    //Fe Case

    G4Material* case_mat = nist -> FindOrBuildMaterial("G4_Fe");

    G4Box* solidCase =
      new G4Box("Case",
                0.5 * Detector_size_xy,
                0.5 * Detector_size_xy,
                0.5 * IronCaseThickness);
    
    G4LogicalVolume* logicCase = 
      new G4LogicalVolume(solidCase, 
                          case_mat,
                           "Case");

    
      new G4PVPlacement(0, 
                        G4ThreeVector(0, 0, Detector_offset_z - 0.009*m), 
                        logicCase, 
                        "Case", 
                        logicWorld, 
                        false, 
                        3, 
                        true);
                      

    G4Box* solidCase2 =
      new G4Box("Case2",
                0.5 * Detector_size_xy,
                0.5 * Detector_size_xy,
                0.5 * IronCaseThickness);
    
    G4LogicalVolume* logicCase2 = 
      new G4LogicalVolume(solidCase2, 
                          case_mat,
                           "Case2");

    
      new G4PVPlacement(0, 
                        G4ThreeVector(0, 0, Detector_offset_z + 0.009*m), 
                        logicCase2, 
                        "Case2", 
                        logicWorld, 
                        false, 
                        4, 
                        true);

    G4Box* solidCase3 =
      new G4Box("Case3",
                0.5 * Detector_size_xy,
                0.5 * Detector_size_xy,
                0.5 * IronCaseThickness);
    
    G4LogicalVolume* logicCase3 = 
      new G4LogicalVolume(solidCase3, 
                          case_mat,
                           "Case3");

    
      new G4PVPlacement(0, 
                        G4ThreeVector(0, 0, Detector_offset_z +151.*mm), 
                        logicCase3, 
                        "Case3", 
                        logicWorld, 
                        false, 
                        5, 
                        true);

    G4Box* solidCase4 =
      new G4Box("Case4",
                0.5 * Detector_size_xy,
                0.5 * Detector_size_xy,
                0.5 * IronCaseThickness);
    
    G4LogicalVolume* logicCase4 = 
      new G4LogicalVolume(solidCase4, 
                          case_mat,
                           "Case4");

    
      new G4PVPlacement(0, 
                        G4ThreeVector(0, 0, Detector_offset_z + 169.*mm), 
                        logicCase4, 
                        "Case4", 
                        logicWorld, 
                        false, 
                        6, 
                        true);

  // Contreate floor
  G4Material* concrete_mat = nist -> FindOrBuildMaterial("G4_CONCRETE");

  G4Box* solidFloor = 
    new G4Box("Floor",
                0.5 * Floor_size_xy,
                0.5 * Floor_size_xy,
                0.5 * Floor_size_z);

  G4LogicalVolume* logicFloor =
    new G4LogicalVolume(solidFloor,
                        concrete_mat,
                        "Floor");
  
  new G4PVPlacement(0,
                    G4ThreeVector(0, 0, Detector_offset_z - GapBetweenScintillatorAndFloor),
                    logicFloor,
                    "Floor",
                    logicWorld,
                    false,
                    7,
                    true);

  // Iron roof
  G4Material* roof_mat = nist -> FindOrBuildMaterial("G4_Fe");
  G4RotationMatrix* rotation_matrix = new G4RotationMatrix();
  rotation_matrix->rotateX(Roof_angle);


  G4Box* solidRoof = 
    new G4Box("Roof",
                0.5 * Roof_size_xy,
                0.5 * Roof_size_xy,
                0.5 * Roof_size_z);

  G4LogicalVolume* logicRoof =
    new G4LogicalVolume(solidRoof,
                        roof_mat,
                        "Roof");
  
  new G4PVPlacement(rotation_matrix,
                    G4ThreeVector(0, 0, Detector_offset_z + 0.5*m),
                    logicRoof,
                    "Roof",
                    logicWorld,
                    false,
                    8,
                    true);

    return physWorld;

}
