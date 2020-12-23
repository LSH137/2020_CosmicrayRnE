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
        fof2 = 0;
        hmf2 = 0;
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
    double fof2;
    double hmf2;
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
char dir[100] = "/media/lsh/CosmicrayRnE/RadioData/MagIch_2019_half/MagIch_2019Txt";
char graph_name[250];
char trash[10];
bool flag = 0;


void FoF2_HmF2()
{
    auto mg = new TMultiGraph();
    auto c_fof2 = new TCanvas("radio_FoF2_data","radio_FoF2_data",1200, 600);
    auto c_hmf2 = new TCanvas("radio_HmF2_data","radio_HmF2_data",1200, 600);
    TGraph* g_fof2 = new TGraph();
    TGraph* g_hmf2 = new TGraph();

    fp_data = fopen("/media/lsh/CosmicrayRnE/RadioData/IonohmF2Ich_2019/FoF2_HmF2data.txt", "r");
    if(fp_data != nullptr)
    {
        
        fscanf(fp_data, "%s %s %s %s %s %s %s %s", trash, trash, trash, trash, trash, trash, trash, trash);
        while(!feof(fp_data))
        {
            if(EOF != fscanf(fp_data, "%d %d %d %d %d %d %lf %lf", &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.sec, &data.fof2, &data.hmf2))
            {
                data.ConvertTime();

                g_fof2->SetPoint(g_fof2->GetN(), data.time, data.fof2);
                g_hmf2->SetPoint(g_hmf2->GetN(), data.time, data.hmf2);
            }
            fclose(fp_data);
        }

        c_fof2->cd();
        g_fof2->SetTitle("FoF2");
        g_fof2->GetXaxis()->SetTitle("time [s]");
        g_fof2->GetYaxis()->SetTitle("FoF2 [Hz]");
        g_fof2->SetMarkerColor(2);
        g_fof2->SetLineColor(3);
        g_fof2->SetMarkerStyle(2);

        g_fof2->Draw("APL");

        //sprintf(graph_name, , start_year, start_month, start_day, end_year, end_month, end_day);
        c_fof2->SaveAs("/media/lsh/CosmicrayRnE/Processed/RadioData/FoF2/FoF2.png");


        c_hmf2->cd();
        g_hmf2->SetTitle("HmF2");
        g_hmf2->GetXaxis()->SetTitle("time [s]");
        g_hmf2->GetYaxis()->SetTitle("HmF2 [Hz]");
        g_hmf2->SetMarkerColor(2);
        g_hmf2->SetLineColor(3);
        g_hmf2->SetMarkerStyle(2);

        g_hmf2->Draw("APL");
        c_hmf2->SaveAs("/media/lsh/CosmicrayRnE/Processed/RadioData/FoF2/HmF2.png");

    }
}