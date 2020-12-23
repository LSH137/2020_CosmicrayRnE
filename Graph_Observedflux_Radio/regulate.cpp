#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

const char CSV[5] = {"csv"};
const char TXT[5] = {"txt"};
const char PATH[150] ={"/media/lsh/CosmicrayRnE/Processed/ob_lv1"};

struct ObData
{
    long long int time = 0;
    int year = 0, month = 0, day = 0, hour = 0, minute = 0, sec = 0;
    int total_edep_ch2 = 0;
    int total_edep_ch3 = 0;
};

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


FILE* fp_data;
FILE* fp_zip;
char dir[250];
char dir2[250];
int nData;
ObData data;
int r_index;
int is_first = TRUE;
long long int pivot_time;
char file_name[1000][150];
double avr_ratio;
int err;

int main(void)
{
    double* ratio = new double[864000];
    fp_zip = fopen64("/media/lsh/CosmicrayRnE/Processed/ratio/requlated.txt", "w");
    if(fp_zip != nullptr)
    {
        sprintf(dir, "%s/2020", PATH);
        nData = FileName(dir, file_name, TXT);

        for(int i = 0; i < nData; i++)
        {
            sprintf(dir2, "%s/%s.txt", dir, file_name[i]);
            fp_data = fopen(dir2, "r");

            if(fp_data != nullptr)
            {
                if(fscanf(fp_data, "%lld %d %d %d %d %d %d %d %d", &data.time, &data.year, &data.month, &data.day, &data.hour, &data.minute, &data.sec, &data.total_edep_ch2, &data.total_edep_ch3) == EOF)
                    break;
                
                if(data.total_edep_ch3 != 0 )
                {
                    ratio[r_index] = ((double)data.total_edep_ch2/(double)data.total_edep_ch3);
                    r_index++;
                }  

                if(is_first == TRUE)
                    pivot_time = data.time;

                is_first = FALSE;

                if(abs(data.time - pivot_time) >= 86400)
                {
                    pivot_time = data.time;
                    for(int k = 0; k < r_index; k++)
                        avr_ratio = avr_ratio + ratio[k]/r_index;
                    
                    fprintf(fp_zip, "%lld %lf\n", data.time, avr_ratio);
                    avr_ratio = 0;
                }
                fclose(fp_data);
            }
            else 
                printf("fp_data open error\n");
        }
        fclose(fp_zip);
    }
    else 
        printf("fp_zip error\n");
    
}