//
// Created by lsh on 20. 4. 2..
//

#ifndef DATAPROCESS_VER6L_CLASS_H
#define DATAPROCESS_VER6L_CLASS_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

#include "Constant.h"


long long int MonthToDay(int year, int month);

class Flux
{
public:
    Flux()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        flux = 0;
        time = 0;
    }
    ~Flux() = default;



    void ConvertTime() // second past after 2019/1/1 0:0:0
    {
        unsigned long long int daypass;
        daypass = (year-2019) * 365 + MonthToDay(year, month) + day;
        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

    unsigned long long int time;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int flux;
};

class Time
{
public:
    Time()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        time = 0;
    }

    ~Time()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        time = 0;
    }

    void ConvertTime() // second past after 2019/1/1/0/0
    {
        unsigned long long int daypass;
        daypass = (year - 2019) * 365 + MonthToDay(year, month) + day;

        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    unsigned long long int time;
};



class Edep
{
public:
    Edep()
    {
        time = 0;
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        minute = 0;
        sec = 0;
        peak_time1 = 0;
        peak_time2 = 0;
    }
    ~Edep() = default;

    int edep_data_ch2_sort[95] = {0};
    int edep_data_ch3_sort[95] = {0};

    unsigned long long int time;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
    int peak_time1;
    int peak_time2;

    int edep_ch2[100] = {0};
    int edep_ch3[100] = {0};
    double derivativeData_ch2[100] = {0};
    double derivativeData_ch3[100] = {0};



    void ConvertTime() // second past after 2019/1/1/0/0
    {
        unsigned long long int daypass;

        daypass = (year-2019) * 365 + MonthToDay(year, month) + day;
        time = daypass * 86400 + hour * 3600 + minute * 60 + sec;
    }

};


struct CloudData
{
    unsigned long long int time = 0;
    int totc = 0;
    int fog = 0;
    int lowc = 0;
    int midc = 0;
    int highc = 0;
};

struct G4Data
{
    int particle = 0;
    double energy = 0;
    double total_edep_ch2 = 0.0;
    double total_edep_ch3 = 0.0;
};

struct ObData
{
    int total_edep_ch2 = 0.0;
    int total_edep_ch3 = 0.0;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, sec = 0;
    long long int time = 0;
};

template <class T>

class Histogram
{
public:
    Histogram()
    {
        index = 0;
        time = 0;
        energy = 0;
    }
    ~Histogram()
    {
        delete [] section;
        delete [] temp;
    }

    double energy;
    unsigned long long int time;
    T* section = new T[1000];

    void SetTime(unsigned long long int t)
    {
        time = t;
    }

    void ReadData(T n)
    {
        if(index < 5000000)
        {
            temp[index] = n;
            index++;
        }
        else{
            //printf(">>error: Entry is to large\r");
        }
    }

    void GetHistogram()
    {
        if(index != 0)
        {
            for(int i = 1; i < index; i++)
            {
                for(int j = 1; j < 600; j++)
                {
                    if(temp[i] > 10*j && temp[i] < j*11)
                    {
                        section[j]++;
                        break;
                    }
                }
            }
        }
        else{
            printf(">>error: no data\n");
        }
    }

    void flush()
    {
        index = 0;
    }

private:
    int* temp = new int[5000000];
    int index;
};

struct Histogram_pack_int
{
    Histogram<int> hist_ch2[MaxParticlenum];
    Histogram<int> hist_ch3[MaxParticlenum];
    Histogram<int> hist_total[MaxParticlenum];

    int year = 0, month = 0, day = 0, hour = 0;
};

struct Histogram_pack_double
{
    Histogram<double> hist_ch2_mu[MaxParticlenum];
    Histogram<double> hist_ch3_mu[MaxParticlenum];
    Histogram<double> hist_total_mu[MaxParticlenum];

    Histogram<double> hist_ch2_e[MaxParticlenum];
    Histogram<double> hist_ch3_e[MaxParticlenum];
    Histogram<double> hist_total_e[MaxParticlenum];

    int year = 0, month = 0, day = 0, hour = 0;
};





#endif //DATAPROCESS_VER6L_CLASS_H
