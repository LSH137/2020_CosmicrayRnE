#include<stdio.h>
#include "TH1.h"
#include "Riostream.h"
#include "Constant.h"
#include <string.h>
#include <dirent.h>

#define TRUE 1
#define FALSE 0

int FileName(const char d[150], char(*file_name)[150], const char type[])
{
    DIR *path;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    int name_index = 0;

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

struct ObData
{
    long long int time = 0;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, sec = 0;
    int total_edep_ch2 = 0;
    int total_edep_ch3 = 0;
};

char file_name[1000][150];
int nfile;
int nData;
char dir[250];
char path[250];
int year;
int is_first = TRUE;
int cnt;
double total;
double excess;
double less_;
double ratio_;
int count_;
long long int pivot_time;

void ObservedGraph()
{
    FILE* fp_data;
    ObData data;
    TFile *fp = new TFile("observed_edep.root", "RECREATE");
    auto canvas_hist = new TCanvas("observated_data_hist","observated_data_hist",800, 600);
    auto c_excess_total = new TCanvas("observated_data_excess_total:time","observated_data_excess_total:time",800, 600);
    auto c_less_total = new TCanvas("observated_data_less_total:time","observated_data_less_total:time",800, 600);
    auto c_less_excess = new TCanvas("observated_data_less_excess","observated_data_less_excess",800, 600);

    TH1D* hist = new TH1D("ch2/ch3", "ch2/ch3", 200, 0, 5);
    TGraph* graph_excess_total = new TGraph();
    TGraph* graph_less_excess = new TGraph();
    TGraph* graph_less_total = new TGraph();

    printf("year: ");
    scanf("%d", &year);

    //printf("=======================debug point 1===================\n");
    sprintf(dir, "%s/%d", Lv1DataDir, year);
    nfile = FileName(dir, file_name, TXT);
    //printf("=======================debug point 2===================\n");
    for(int i = 0; i < nfile; i++)
    {
        printf("%f %% end\r", (float)i / (float)nfile * 100);
        //printf("=======================debug point 3===================\n");
        sprintf(path, "%s/%s.txt", dir, file_name[i]);
        printf("%d_%s\n", i, path);

        //puts(dir);
        //sleep(3);
        fp_data = fopen64(path, "r");

        count_ = 0;
        if(fp_data != nullptr)
        {
            //printf("=======================debug point 4===================\n");
            is_first = TRUE;
            while(!feof(fp_data) && count_ < 100000)
            {
                //printf("=======================debug point 5===================\n");
                count_++;
                fscanf(fp_data, "%lld %d %d %d %d %d %d %d %d", &data.time, &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.sec, &data.total_edep_ch2, &data.total_edep_ch3);

                //printf("%lld %d %d %d %d %d %d %d %d\n", data.time, data.year, data.month, data.day, data.hour, data.minute, data.sec, data.total_edep_ch2, data.total_edep_ch3);
                //printf("=======================debug point 6===================\n");
                if(data.total_edep_ch3 != 0)
                    hist -> Fill((double)data.total_edep_ch2/(double)data.total_edep_ch3);

                //printf("=======================debug point 7===================\n");
                
                if(is_first == TRUE)
                    pivot_time = data.time;

                //printf("=======================debug point 8===================\n");
                   
                if(abs(data.time - pivot_time) >= Hour)
                {
                    pivot_time = data.time;
                    //printf("=======================debug point 9===================\n");
                    cnt++;
                    for(int i = 0; i < 200; i++)
                        total = total + hist->GetBinContent(i);

                    //printf("=======================debug point 10===================\n");
        
                    for(int i = 40; i < 200; i++)
                        excess = excess + hist->GetBinContent(i);

                    //printf("=======================debug point 11===================\n");

                    less_ = total - excess;

                    if(total != 0)
                        ratio_ = excess / total;

                   //printf("=======================debug point 12===================\n");

                    //printf("ratio_e/s = %f\t", ratio_);

                    //printf("=======================debug point 13===================\n");

                    if(data.time != 0)
                        graph_excess_total -> SetPoint(graph_excess_total->GetN(), data.time, ratio_);

                    //printf("=======================debug point 14===================\n");

                    if(excess != 0)
                        ratio_ = less_ / excess;

                    //printf("=======================debug point 15===================\n");

                   // printf("ratio_l/e = %f\t", ratio_);
                    
                    if(data.time != 0)
                        graph_less_excess -> SetPoint(graph_less_excess->GetN(), data.time, ratio_);

                    //printf("=======================debug point 16===================\n");

                    if(total != 0)
                        ratio_ = less_ / total;

                    //printf("=======================debug point 17===================\n");

                    //printf("ratio_l/t = %f\n", ratio_);
                    
                    //printf("=======================debug point 18===================\n");
                    if(data.time != 0)
                        graph_less_total -> SetPoint(graph_less_total->GetN(), data.time, ratio_);

                    //printf("=======================debug point 19===================\n");


                    ratio_ = 0;
                    total = 0;
                    excess = 0;
                    less_ = 0;

                    //printf("=======================debug point 20===================\n");
                    canvas_hist->cd();
                    hist -> Draw();
                    //printf("=======================debug point 21===================\n");
                    sprintf(path, "%s/%d_observed_ch2ch3.png", Histogram_Dir, cnt);
                    canvas_hist->SaveAs(path);
                    //printf("=======================debug point 22===================\n");
                    //fp -> Write();
                    hist -> Reset();
                }
                is_first = FALSE;
                //printf("=======================debug point 23===================\n");
            }

            fclose(fp_data);
            //printf("=======================debug point 24===================\n");
        }
        else
            printf("error");

        //printf("=======================debug point 25===================\n");
    }

    //printf("=======================debug point 26===================\n");
    c_excess_total -> cd();
    graph_excess_total -> SetTitle("observe excess/total:time");
    graph_excess_total -> SetMarkerColor(6);
    graph_excess_total -> SetMarkerSize(1.0);
    graph_excess_total -> SetMarkerStyle(34);
    graph_excess_total -> GetXaxis()->SetTitle("date[s]");
    graph_excess_total -> GetYaxis()->SetTitle("excess/total");

    graph_excess_total -> Draw("AP");

    c_excess_total -> SaveAs("observe excess_total:time.png");

    //printf("=======================debug point 27===================\n");
    c_less_total -> cd();
    graph_less_total -> SetTitle("observe less/total:time");
    graph_less_total -> SetMarkerColor(6);
    graph_less_total -> SetMarkerSize(1.0);
    graph_less_total -> SetMarkerStyle(34);
    graph_less_total -> GetXaxis()->SetTitle("date[s]");
    graph_less_total -> GetYaxis()->SetTitle("less/total");

    graph_less_total -> Draw("AP");

    c_less_total -> SaveAs("observe less_total:time.png");

    //printf("=======================debug point 28===================\n");
    c_less_excess -> cd();
    graph_less_excess -> SetTitle("observe less/excess:time");
    graph_less_excess -> SetMarkerColor(6);
    graph_less_excess -> SetMarkerSize(1.0);
    graph_less_excess -> SetMarkerStyle(34);
    graph_less_excess -> GetXaxis()->SetTitle("date[s]");
    graph_less_excess -> GetYaxis()->SetTitle("less/excess");

    graph_less_excess -> Draw("AP");

    c_less_total -> SaveAs("observe less_excess:time.png");
    //printf("=======================debug point 29===================\n");
}
