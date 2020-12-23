#include<stdio.h>
#include "TH1.h"
#include "Riostream.h"
#include "Constant.h"
#include <algorithm>

#define TRUE 1
#define FALSE 0
#define DEBUG 0


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
class SFU
{
public:
    SFU()
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
    ~SFU()
    {

    }
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int sfu;
    int time;

    void ConvertTime() // second past after 2019/1/1 0:0:0
    {
        int daypass;
        daypass = (year-2019) * 365 + MonthToDay(year, month) + day;
        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

};

struct Obflux
{
    int time = 0;
    int flux = 0;
};

int year = 0;
int month = 0;
int day = 0;
int hour = 0;
int minute = 0;
int sec = 0;

int average[2][10000];

void Result()
{
    FILE* fp_data;
    FILE* fp_radio;
    TGraph* g = new TGraph();
    Obflux* data = new Obflux[12000000]; 
    SFU* rdata = new SFU[10000];
    int d_index = 0;
    int r_index = 0;
    auto c = new TCanvas("ratio:SFU","ratio:SFU",800, 600);

    if(DEBUG)
    printf("debug 1\n");

    //open radio data
    fp_radio = fopen("/media/lsh/CosmicrayRnE/RadioData/SFU.csv", "r");
    fp_data = fopen("/media/lsh/CosmicrayRnE/ObservedData/flux/flux.txt", "r");

    if(DEBUG)
    printf("debug 2\n");

    if(fp_data != nullptr && fp_radio != nullptr)
    {
        if(DEBUG)
        printf("debug 3\n");

        while(!feof(fp_data))
        {
            if(DEBUG)
            printf("debug 4\n");

            if(fscanf(fp_data, "%d %d %d %d %d %d %d %d", &data[d_index].time, &year, &month, &day, &hour, &minute, &sec, &data[d_index].flux) == EOF)
                break;

            if(DEBUG)
            printf("debug 5\n");

            d_index++;
        }

        while(!feof(fp_radio))
        {
            if(DEBUG)
            printf("debug 6\n");

            if(EOF != fscanf(fp_radio, "%d, %d, %d, %d", &rdata[r_index].year, &rdata[r_index].month, &rdata[r_index].day, &rdata[r_index].sfu))
            {
                if(DEBUG)
                printf("debug 7\n");

                rdata[r_index].ConvertTime();

                if(DEBUG)
                printf("debug 8\n");
                r_index++;
            }
            if(DEBUG)
            printf("debug 9\n");
        }
        
        if(DEBUG)
            printf("debug 10\n");

        fclose(fp_radio);
        fclose(fp_data);
    }
    else
    {
        printf("error");
        exit(-1);
    }
       
    


    for(int i = 0; i < r_index; i++)
        for(int j = 0; j < d_index; j++)
        {
            if(DEBUG)
            printf("debug 11\n");
            
            if(abs(rdata[i].time - data[j].time) < 100 )
                
                g->SetPoint(g->GetN(), rdata[i].sfu, data[j].flux);
        }

    c -> cd();
    g->SetTitle("flux:sfu");
    g->SetMarkerColor(6);
    g->SetMarkerSize(1.0);
    g->SetMarkerStyle(34);
    g->GetXaxis()->SetTitle("sfu[Jy * 10^4]");
    g->GetYaxis()->SetTitle("flux [m^-2]");

    g->Draw("AP");

    c -> SaveAs("observe flux:sfu_flux<NoLimit.png");

    delete[] data; 
    delete[] rdata;
}
