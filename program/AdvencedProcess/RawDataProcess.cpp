#include <cstdio>
#include <cstdlib>
#include "FileIO.h"
#include "Constant.h"
#include "Class.h"

class Event
{
public:
    Event()
    {
        year = 0;
        month = 0;
        day = 0;
        hour = 0;
        min = 0;
        sec = 0;
        time = 0;
        
        /*
        for(int i = 0; i < 100; i++)
        {
            ch2[i] = 0;
            ch3[i] = 0;
        }
        */
    }
    ~Event()
    {

    }

    void ConvertTime() // second past after 2016/1/1/0/0
    {
        unsigned long long int daypass;
        daypass = (year - 2016) * 365 + MonthToDay(year, month) + day;

        time = daypass * 86400 + hour * 3600 + min * 60 + sec;
    }

    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    unsigned long long int time;
    //int ch2[100];
    //int ch3[100];
};

inline int CompareTime(const Event& now, const Event& old)
{
    if(now.year == old.year)
        if(now.month == old.month)
            if(now.day == old.day)
                if(now.hour == old.hour)
                    if(now.min == old.min)
                        if(now.sec == old.sec)
                            return 1;

    return 0;
}

FILE* fp_data;
FILE* fp_processed;

char file_name[Filenum + 10][150];
char RawDataDir[150];
int data_year = 2016;
int nfile;
int temp[5];
int error;
long long int total_edep_ch2;
long long int total_edep_ch3;
int number_of_event;
int escape; 
int flux;
int day;
int first = 1;
Event now;
Event old;

int main(void)
{
    char dir[250];
    printf("year: ");
    scanf("%d", &data_year);

    sprintf(RawDataDir, "/media/cosmicray/새 볼륨/%d", data_year);
    nfile = FileName(RawDataDir, file_name, TXT);
    

    for(int f = 0; f < nfile; f++)
    {
        sprintf(dir, "%s/%s.txt", RawDataDir, file_name[f]);
        printf("%d.input: %s\n",f, dir);
        fp_data = fopen64(dir, "r");
        //printf("==================debug point 1====================\n");

        if(fp_data != nullptr)
        {
            //printf("==================debug point 2====================\n");
            while(!feof(fp_data) && escape < MaxEdepNumber)
            {
                //printf("==================debug point 3====================\n");
                fscanf(fp_data, "%d %d  %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);

                for (int i = 1; i <= 6; i++)
                {
                    //printf("==================debug point 4====================\n");
                    fscanf(fp_data, "%d %d %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);

                    if(i == 1)
                    {
                        now.year = temp[2] * 256 + temp[3];
                        now.month = temp[4];
                    }
                    else if(i == 2)
                    {
                        now.day = temp[1];
                        now.hour = temp[2];
                        now.min = temp[3];
                        now.sec = temp[4];
                    }
                } // time data end
                
                //printf("==================debug point 5====================\n");
                // consider if the time data have problem
                if(now.year > 2020 || now.month > 12 || now.day > 31 || now.hour > 24 || now.min > 59 || now.sec > 59)
                {
                    //printf("==================debug point 6====================\n");
                    //printf(">>thread %d: time information is wrong in file %s\r", threadnum, file_name[k]);
                    for (int i = 0; i <= 94; i++)
                    {
                        //printf("==================debug point 7====================\n");
                        error = fscanf(fp_data, "%d %d %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);
                        if(error)
                        { }

                    } // do nothing just reading
                }
                else //if there is no problem in time data
                {
                    //printf("==================debug point 8====================\n");
                    for (int i = 0; i <= 94; i++) //read edep
                    {
                        //printf("==================debug point 9====================\n");
                        error = fscanf(fp_data, "%d %d %d %d %d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);
                        if(error)
                        {
                            //printf("==================debug point 10====================\n");
                            int regular[2];
                            regular[0] = (1024 - temp[2]) - 100;
                            regular[1] = (1024 - temp[3]) - 100;

                            if(regular[0] < 0) regular[0] = 0;
                            if(regular[1] < 0) regular[1] = 0;
                            total_edep_ch2 = total_edep_ch2 + regular[0];
                            total_edep_ch3 = total_edep_ch3 + regular[1];
                        }
                        //printf("==================debug point 11====================\n");

                    } // data read end;

                    // calculate flux
                    /*
                    if(escape > 0)
                    {
                        if(CompareTime(now, old))
                            flux++;
                        else
                        {
                            old.ConvertTime();
                            fprintf(fp_flux[threadnum], "%llu %d %d %d %d %d %d %d\n",old.time, old.year, old.month, old.day, old.hour, old.min, old.sec, flux+1);
                            flux = 0;
                        }
                    }
                    */
                    //old_time = time;
                    //CopyTime(now, old);
                    old = now;
                    number_of_event++;
                    
                    //save total energy deposition
                    //printf("==================debug point 1====================\n");
                    if(f % 100 == 0)
                    {
                        //printf("==================debug point 2====================\n");
                        if(fp_processed != nullptr)
                            fclose(fp_processed);
                        
                        //printf("==================debug point 3====================\n");
                        sprintf(dir, "/media/cosmicray/새 볼륨/processed/%d/%d-%d-%d_%d.txt", data_year, now.year, now.month, now.day, f);
                       // printf("==================debug point 4====================\n");
                        fp_processed = fopen64(dir, "w");
                        //printf("==================debug point 5====================\n");
                    }
                    //printf("==================debug point 13====================\n");

                    if(fp_processed != nullptr)
                    {
                        //printf("==================debug point 14====================\n");
                        day = now.day;
                        //printf("==================debug point 15====================\n");
                        now.ConvertTime();
                        //printf("==================debug point 16====================\n");
                        fprintf(fp_processed, "%llu %d %d %d %d %d %d %lld %lld\n",now.time, now.year, now.month, now.day, now.hour, now.min, now.sec, total_edep_ch2, total_edep_ch3);

                        //printf("==================debug point 17====================\n");
                    }
                    else
                        printf("writing error\n");

                    //printf("==================debug point 18====================\n");

                    /*
                    if(day != now.day && first != 1)
                    {
                        printf("==================debug point 12 %d====================\n", first);
                        fclose(fp_processed);
                        first = 0; // first = FALSE
                       
                    }
                    else
                    {
                        printf("==================debug point 14====================\n");
                        first = 0; // first = FALSE
                        sprintf(dir, "/media/cosmicray/새 볼륨/processed/2016/%d/%d-%d-%d.txt", data_year, now.year, now.month, now.day);
                        fp_processed = fopen64(dir, "a");

                        if(fp_processed != nullptr)
                        {
                            printf("==================debug point 15====================\n");
                            now.ConvertTime();
                            fprintf(fp_processed, "%llu %d %d %d %d %d %d %lld %lld\n",now.time, now.year, now.month, now.day, now.hour, now.min, now.sec, total_edep_ch2, total_edep_ch3);
                        }
                    }
                    */
                } // end of reading one event
                //printf("==================debug point 16====================\n");
                escape++;

                total_edep_ch2 = 0;
                total_edep_ch3 = 0;

            }
            //printf("==================debug point 17====================\n");
            fclose(fp_data);
        }
        else 
            printf("error occur while opening RawData\n");

        //printf("==================debug point 18====================\n");
    }
    //printf("==================debug point 19====================\n");
}