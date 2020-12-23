//
// Created by lsh on 20. 3. 4..
//

#ifndef DATAPROCESS_VER6L_CONSTANT_H
#define DATAPROCESS_VER6L_CONSTANT_H

#define Filenum 8000
#define MaxParticlenum 100000
#define MaxProjectnum 500
#define MaxEdepNumber 510000000
#define MaxFluxIn1Hour 1000000
#define Hour 3600
#define divide 10

//#define Daynum 1000
const char RawDataDir[150] ={"/media/lsh/CosmicrayRnE/ObservedData/RawData"};
const char Lv1DataDir[150] ={"/media/lsh/CosmicrayRnE/ObservedData/Lv1_data"};
const char FluxDataDir[150] = {"/media/lsh/CosmicrayRnE/ObservedData/flux"};
const char SimulationDataDir[150] = {"/media/lsh/CosmicrayRnE/SimulatedData/AdvencedG4Data"};
//const char eSimulationDataDir[150] = {"/media/cosmicray/CosmicrayRnE/SimulatedData/G4Data_e"};
//const char pSimulationDataDir[150] = {"/media/cosmicray/CosmicrayRnE/SimulatedData/G4Data_proton"};



const char CSV[5] = {"csv"};
const char TXT[5] = {"txt"};

#endif //DATAPROCESS_VER6L_CONSTANT_H
