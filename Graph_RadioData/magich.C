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

class MagData
{
public:

    MagData()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        H = 0;
        D = 0;
        Z = 0;
        P = 0;
        time = 0;
    }
    ~MagData()
    {

    }
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    double H;
    double D;
    double Z;
    double P;
    unsigned long long int time;

    void ConvertTime() // second past after 2019/1/1 0:0:0
    {
        unsigned long long int daypass;
        daypass = (year-2019) * 365 + MonthToDay(year, month) + day;
        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

};

class FileInfo
{
public:
    FileInfo()
    {
        
    }
    ~FileInfo()
    {

    }

    char FileName[250];
    int year;
    int month;
    int day;

    void GetName(char* dir)
    {
        sprintf(FileName, "%s/MagIch_%04d%02d%02d.txt", dir, year, month, day);
    }
};

MagData data;
FileInfo file;
FILE* fp_data;
char dir[100] = "/media/lsh/CosmicrayRnE/RadioData/MagIch_2019_half/MagIch_2019Txt";
char graph_name[250];
char trash[10];
int start_year;
int end_year;
int start_month;
int end_month;
int start_day;
int end_day;
bool flag = 0;


void magich()
{
    auto mg = new TMultiGraph();
    auto C = new TCanvas("radio_data","radio_data",1200, 600);
    TGraph* g_magich = new TGraph();

    printf("enter start year month day: ");
    scanf("%d %d %d", &start_year, &start_month, &start_day);

    printf("enter end year month, day: ");
    scanf("%d %d %d", &end_year, &end_month, &end_day);

    for(int year = start_year; year <= end_year; year++)
        for(int month = start_month; month <= end_month; month++)
            for(int day = start_day; day <= end_day; day++)
            {
                //printf("\n--------debug point 1----------\n");
                flag = 1;
                file.year = year;
                file.month= month;
                file.day = day;
                file.GetName(dir);

                printf("%s\n", file.FileName);
                
                fp_data = fopen(file.FileName, "r");
                if(fp_data != nullptr)
                {
                    //printf("\n--------debug point 3----------\n");
                    fscanf(fp_data, "%s %s %s %s %s %s %s %s %s %s", trash, trash, trash, trash, trash, trash, trash, trash, trash, trash);
                    
                    while(!feof(fp_data))
                    {

                        if(EOF != fscanf(fp_data, "%d, %d, %d, %d, %d, %d, %lf, %lf, %lf, %lf", &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.sec, &data.H, &data.D, &data.Z, &data.P))
                        {
                            //printf("\n--------debug point 4----------\n");
                            data.ConvertTime();
                            g_magich->SetPoint(g_magich->GetN(), data.time, data.Z);
                        }
                    }
                    fclose(fp_data);
                    //printf("\n--------debug point 5----------\n");
                }
                else
                    printf("file open error\n");
                
                
                //printf("\n--------debug point 6----------\n");
            }

    if(flag == 1)
    {
        //printf("\n--------debug point 7----------\n");
        C->cd();
        g_magich->SetTitle("magich data_Bz[nT]");
        g_magich->GetXaxis()->SetTitle("time [s]");
        g_magich->GetYaxis()->SetTitle("earth magnet [nT]");
        g_magich->SetMarkerColor(2);
        g_magich->SetLineColor(3);
        g_magich->SetMarkerStyle(2);

        g_magich->Draw("APL");

        sprintf(graph_name, "/media/lsh/CosmicrayRnE/Processed/RadioData/magich/%d:%d:%d-%d:%d:%d_magich_Bz.png", start_year, start_month, start_day, end_year, end_month, end_day);
        C->SaveAs(graph_name);

    }
    
}