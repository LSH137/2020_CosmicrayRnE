#include "Riostream.h"
#include <stdio.h>
#include <stdlib.h>

long long int MonthToDay(int year, int month)
{
    switch (month) {
        case 1:
            return 0;
        case 2:
            return 31;
        case 3:
        {
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return MonthToDay(year, 2) + 29;
            else return MonthToDay(year, 2) + 28;
        }
        case 4:
            return 31 + MonthToDay(year, 3);
        case 5:
            return 30 + MonthToDay(year, 4);
        case 6:
            return 31 + MonthToDay(year, 5);
        case 7:
            return 30 + MonthToDay(year, 6);
        case 8:
            return 31 + MonthToDay(year, 7);
        case 9:
            return 31 + MonthToDay(year, 8);
        case 10:
            return 30 + MonthToDay(year, 9);
        case 11:
            return 31 + MonthToDay(year, 10);
        case 12:
            return 30 + MonthToDay(year, 11);
        default:
            return 0;
    }
}

class FH
{
public:
    FH()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        sfu = 0;
        time = 0;
    }
    ~FH()
    {

    }
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int sfu;
    unsigned long long int time;

    void ConvertTime() // second past after 2019/1/1 0:0:0
    {
        unsigned long long int daypass;
        daypass = (year-2019) * 365 + MonthToDay(year, month) + day;
        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

};


FH data;
FILE* fp_data;
char dir[100] = "/media/lsh/CosmicrayRnE/RadioData/";
char graph_name[250];
char trash[10];
bool flag = 0;


void sfu()
{
    auto mg = new TMultiGraph();
    auto c = new TCanvas("radio_SFU_data","radio_SFU_data",1200, 600);
    TGraph* g_sfu = new TGraph();

    fp_data = fopen("/media/lsh/CosmicrayRnE/RadioData/SFU.csv", "r");
    if(fp_data != nullptr)
    {
        //fscanf(fp_data, "%s %s %s %s %s %s %s %s", trash, trash, trash, trash, trash, trash, trash, trash);
        while(!feof(fp_data))
        {
            if(EOF != fscanf(fp_data, "%d, %d, %d, %d", &data.year, &data.month, &data.day, &data.sfu))
            {
                data.ConvertTime();
                if(data.time < 50000000)
                    g_sfu->SetPoint(g_sfu->GetN(), data.time, data.sfu);
                
            }
        }
        fclose(fp_data);

        //c->cd();
        g_sfu->SetTitle("SFU");
        g_sfu->GetXaxis()->SetTitle("time [s]");
        g_sfu->GetYaxis()->SetTitle("SolarFluxUnit [10^4Jy]");
        g_sfu->SetMarkerColor(2);
        //g_sfu->SetLineColor(3);
        g_sfu->SetMarkerStyle(2);

        g_sfu->Draw("APL");

        //sprintf(graph_name, "/media/lsh/CosmicrayRnE/Processed/RadioData/SFU/%d:%d:%d-%d:%d:%d_sfu.png", data.year, data.month, data.day);
        c->SaveAs("/media/lsh/CosmicrayRnE/Processed/RadioData/SFU/sfu_2019_time<50000000_APL.png");

    }
    else
        printf("file_open_error\n");
    
}