#include <stdio.h>
#include "Riostream.h"
#include "Constant.h"
#include <string.h>
#include <dirent.h>

#define MaxEnergy 25000
#define Energy 200
#define MaxRatio 1000000
#define DEBUG 0
#define DrawHist 0


int FileName(const char d[150], char(*file_name)[150], const char type[])
{
    int name_index = 0;
    DIR *path;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    
    //printf(">>success to enter FileName\n");
    //printf("FileName(): debug point 1\n");
    path = opendir(d);
    if (path)
    {
        //printf("FileName(): debug point 2\n");
        while ((dir = readdir(path)) != nullptr)
        {
            //printf("FileName(): debug point 3\n");
            p1 = strtok(dir->d_name,".");
            p2 = strtok(nullptr,".");

            if(p2 != nullptr)
            {
                //printf("FileName(): debug point 4\n");
                ret = strcmp(p2,type);

                if(ret == 0)
                {
                    //printf("FileName(): debug point 5\n");
                    strcpy(file_name[name_index], p1);
                    printf("%s\n", p1);
                    name_index ++;
                }
            }
        }
        closedir(path);
    } else
        printf(">>error occur while get data file name\n");

     //printf("FileName(): debug point 6\n");
    return name_index;
    //printf("||FileName end\n");
}

struct G4Data
{
    int particle = 0;
    double energy = 0;
    double total_edep_ch2 = 0.0;
    double total_edep_ch3 = 0.0;
};

int debug = 0;

void Debug(char* message)
{
    if(DEBUG)
    {
        printf("%d - debug point %s\n", debug, message);
        debug++;
    }
    
}

G4Data g4data;

char file_name[10000][150];

void AdvencedSimulation()
{
    FILE* fp_data;
    FILE* fp_histo;
    char trash[50];
    int escape;
    char dir[250];
    char path[250];
    char graph_name[250];
    int nfile;
    double less_1;
    double excess_1;
    double total_integral;
    double ratio;

    //Debug();

    TCanvas* canvas_mu = new TCanvas("mu- simulation_data_total","mu- simulation_data_total",800, 600);
    TCanvas* canvas_e = new TCanvas("e- simulation_data_total","e- simulation_data_total",800, 600);
    TCanvas* canvas_p = new TCanvas("proton simulation_data_total","proton simulation_data_total",800, 600);
    TCanvas* canvas_ratio = new TCanvas("simulation_data_excess:less","simulation_data_less",800, 600);
    //Debug();
    TH1D* hist_mu[MaxEnergy + 5];
    for(int i = 0; i < MaxEnergy; i++)
        hist_mu[i] = new TH1D("mu-_ch2/ch3", "mu-_ch2/ch3", 200, 0, 10);
    //Debug();
    TH1D* hist_e[MaxEnergy + 5];
    for(int i = 0; i < MaxEnergy; i++) 
        hist_e[i] = new TH1D("e-_ch2/ch3", "e-_ch2/ch3", 200, 0, 10);

    TH1D* hist_p[MaxEnergy + 5];
    for(int i = 0; i < MaxEnergy; i++) 
        hist_p[i] = new TH1D("proton_ch2/ch3", "proton_ch2/ch3", 200, 0, 10);
    //Debug();
    TGraph* graph_mu = new TGraph();
    TGraph* graph_e = new TGraph();
    TGraph* graph_p = new TGraph();

    //Debug();
    TMultiGraph* mg = new TMultiGraph();
    //Debug();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    for(int energy = 1; energy <= Energy; energy++)
    {
        sprintf(dir, "%s/%dKeV", SimulationDataDir, (int)(energy*100));
        nfile = FileName(dir, file_name, CSV);

        for(int i = 0; i < nfile; i++)
        {
            Debug("after for i < nfile");
            sprintf(dir, "%s/%dKeV/%s.csv", SimulationDataDir, (int)(energy*100), file_name[i]);
            //printf("DIR: %s\n", dir);
            //sleep(1);
            fp_data = fopen64(dir, "r");
            Debug("after fopen dir");
            if(fp_data != nullptr)
            {
                Debug("if fpdata != nullptr");
                for(int j = 0; j < 20; j++)
                    fscanf(fp_data, "%s", trash);
                Debug("scan trash value");
                while(!feof(fp_data))
                {
                    Debug("while fp_data isn't end");
                    fscanf(fp_data, "%lf,%d,%lf,%lf", &g4data.energy, &g4data.particle, &g4data.total_edep_ch2, &g4data.total_edep_ch3);

                    if(g4data.particle == 0) //muon
                    {
                        Debug("muon");
                        //printf("mu-\n");
                        if(g4data.total_edep_ch3 != 0 && g4data.energy < MaxEnergy)
                            hist_mu[(int)(g4data.energy*10)]->Fill(g4data.total_edep_ch2/g4data.total_edep_ch3);
                    }
                    else if(g4data.particle == 2) //electron
                    {
                       Debug("electron");
                       //printf("electron\n");
                        if(g4data.total_edep_ch3 != 0 && g4data.energy < MaxEnergy)
                            hist_e[(int)(g4data.energy*10)]->Fill(g4data.total_edep_ch2/g4data.total_edep_ch3);
                    }
                    else if(g4data.particle == 3) //proton
                    {
                        Debug("proton");
                        //printf("proton\n");
                        if(g4data.total_edep_ch3 != 0 && g4data.energy < MaxEnergy)
                            hist_p[(int)(g4data.energy*10)]->Fill(g4data.total_edep_ch2/g4data.total_edep_ch3);
                    }
                    Debug("end");

                }
                Debug("before close fp_data");
                fclose(fp_data);
                Debug("after close fp_data");
            }
            else
                printf("error\n");
        }
    }

    //////////////////////////////////////////////////print muon////////////////////////////////////////////////////
    
    for(int e = 1; e <= Energy; e++)
    {
        sprintf(dir, "/media/lsh/CosmicrayRnE/SimulatedData/Histogram_txt/simulation_histogram_muon_%dKeV.csv", e*100);
        fp_histo = fopen64(dir, "w");

        if(fp_histo != nullptr)
        {
            for(int i = 0; i < 200; i++)
                fprintf(fp_histo, "%lf,%lf\n", 0.05*i, hist_mu[e]->GetBinContent(i));

            fclose(fp_histo);
        }

        Debug("draw graph1");
        excess_1 = 0;
        total_integral = 0;
        less_1 = 0;
        Debug("draw graph2");
        for(int i = 0; i < 200; i++)
            total_integral = total_integral + hist_mu[e]->GetBinContent(i);
        Debug("draw graph3");
        for(int i = 20; i < 200; i++)
            excess_1 = excess_1 + hist_mu[e]->GetBinContent(i);
        Debug("draw graph4");
        for(int i = 0; i < 20; i++)
            less_1 = less_1 + hist_mu[e]->GetBinContent(i);
        Debug("draw graph5");
        if(excess_1 > 0)
        {
            ratio = excess_1 /total_integral;  
            if(ratio < MaxRatio)      
                graph_mu->SetPoint(graph_mu->GetN(), e*100, ratio);
        }

        if(DrawHist)
        {
            Debug("draw graph6");
            canvas_mu -> cd();
            Debug("draw graph7");
            hist_mu[e]->Draw();
            //Debug();
            sprintf(graph_name, "/media/lsh/CosmicrayRnE/SimulatedData/result/muon/Advenced_LowEnergy_mu_simulation_ch2divch3_%dKeV.png", (int)(e*100));
            //Debug();
            canvas_mu->SaveAs(graph_name);
        }
        
    }
    //Debug();

    ////////////////////////////////////////////////////print electron////////////////////////////////////////////////

    for(int e = 1; e <= Energy; e++)
    {
        sprintf(dir, "/media/lsh/CosmicrayRnE/SimulatedData/Histogram_txt/simulation_histogram_electron_%dKeV.csv", e*100);
        fp_histo = fopen64(dir, "w");

        if(fp_histo != nullptr)
        {
            for(int i = 0; i < 200; i++)
                fprintf(fp_histo, "%lf,%lf\n", 0.05*i, hist_e[e]->GetBinContent(i));

            fclose(fp_histo);
        }

        Debug("draw graph8");
        excess_1 = 0;
        total_integral = 0;
        less_1 = 0;

        Debug("draw graph9");
        for(int i = 0; i < 200; i++)
            total_integral = total_integral + hist_e[e]->GetBinContent(i);

        Debug("draw graph10");
        for(int i = 20; i < 200; i++)
            excess_1 = excess_1 + hist_e[e]->GetBinContent(i);

        for(int i = 0; i < 20; i++)
            less_1 = less_1 + hist_e[e]->GetBinContent(i);
            
        if(excess_1 > 0)
        {
            ratio = excess_1 /total_integral; 
            if(ratio < MaxRatio)   
                graph_e->SetPoint(graph_e->GetN(), e*100, ratio);
        }
        
        if(DrawHist)
        {
            canvas_e -> cd();
            hist_e[e]->Draw();
            sprintf(graph_name, "/media/lsh/CosmicrayRnE/SimulatedData/result/electron/Advenced_LowEnergy_e_simulation_ch2divch3_%dKeV.png", (int)(e*100));
            canvas_e->SaveAs(graph_name);
        }
        
        //hist_e[e]->Reset();
    }

     ////////////////////////////////////////////////////print proton///////////////////////////////////////////////
    
    for(int e = 1; e <= Energy; e++)
    {
        sprintf(dir, "/media/lsh/CosmicrayRnE/SimulatedData/Histogram_txt/simulation_histogram_proton_%dKeV.csv", e*100);
        fp_histo = fopen64(dir, "w");

        if(fp_histo != nullptr)
        {
            for(int i = 0; i < 200; i++)
                fprintf(fp_histo, "%lf,%lf\n", 0.05*i, hist_p[e]->GetBinContent(i));

            fclose(fp_histo);
        }

        excess_1 = 0;
        total_integral = 0;
        less_1 = 0;

        for(int i = 0; i < 200; i++)
            total_integral = total_integral + hist_p[e]->GetBinContent(i);

        for(int i = 20; i < 200; i++)
            excess_1 = excess_1 + hist_p[e]->GetBinContent(i);

        for(int i = 0; i < 20; i++)
            less_1 = less_1 + hist_p[e]->GetBinContent(i);
            
        if(excess_1 > 0)
        {
            ratio = excess_1 /total_integral; 
            if(ratio < MaxRatio)  
                graph_p->SetPoint(graph_p->GetN(), e*100, ratio);
        }
        
        if(DrawHist)
        {
            canvas_p -> cd();
            hist_p[e]->Draw();
            sprintf(graph_name, "/media/lsh/CosmicrayRnE/SimulatedData/result/proton/Advenced_LowEnergy_p_simulation_ch2divch3_%dKeV.png", (int)(e*100));
            canvas_p->SaveAs(graph_name);
        }
        
        //hist_e->Reset();
    }

        canvas_ratio -> cd();
        graph_mu -> SetTitle("muon excess/total:energy");
        graph_mu -> SetMarkerColor(3);
        graph_mu -> SetLineColor(2);
        graph_mu -> SetLineWidth(2);
        graph_mu -> SetMarkerSize(1.0);
        graph_mu -> SetMarkerStyle(34);

        graph_e -> SetTitle("electron excess/total:energy");
        graph_e -> SetMarkerColor(6);
        graph_e -> SetLineColor(7);
        graph_e -> SetLineWidth(2);
        graph_e -> SetMarkerSize(1.0);
        graph_e -> SetMarkerStyle(22);

        graph_p -> SetTitle("proton excess/total:energy");
        graph_p -> SetMarkerColor(9);
        graph_p -> SetLineColor(8);
        graph_p -> SetLineWidth(2);
        graph_p -> SetMarkerSize(1.0);
        graph_p -> SetMarkerStyle(21);


        mg -> Add(graph_mu);
        mg -> Add(graph_e);
        //mg -> Add(graph_p);

        mg -> GetXaxis()->SetTitle("energy[KeV]");
        mg -> GetYaxis()->SetTitle("excess/total");
        //canvas_ratio -> SetLogx();
        //canvas_ratio -> SetLogy();

        mg -> Draw("APL APL");
        canvas_ratio -> BuildLegend();
        //sprintf(graph_name, "/media/lsh/CosmicrayRnE/SimulatedData/result/Advenced_LowEnergy_excess_total_20MeV_muon_electron_under%d.png", MaxRatio);
        //canvas_ratio -> SaveAs(graph_name);
        //canvas_ratio -> ResetDrawn();
}    
