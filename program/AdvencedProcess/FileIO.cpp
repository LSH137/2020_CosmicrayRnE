//
// Created by lsh on 20. 3. 4..
//

#include "FileIO.h"
#include "Constant.h"
#include <cstdio>
#include <cstring>
#include <dirent.h>

//int runningDay[Daynum];
//extern int numberOfDay;

DIR *path;
char *p1,*p2;
int ret;
struct dirent *dir;

extern FILE* fp_EdepData[Threadnum + 10];

extern FILE* fp_re_EdepData[Threadnum + 10];

//extern char file_name[Filenum + 10][150];
extern  FILE* fp_flux[Threadnum + 10];

extern FILE* fp_re_flux[Threadnum];

/////////////////////////////////////////////////////////////////////////////////////////


int FileName(const char d[150], char(*file_name)[150], const char type[])
{
    int name_index = 0;

    //printf(">>success to enter FileName\n");

    path = opendir(d);
    if (path)
    {
        while ((dir = readdir(path)) != nullptr)
        {
            p1 = strtok(dir->d_name,".");
            p2 = strtok(nullptr,".");

            if(p2 != nullptr)
            {
                ret = strcmp(p2,type);

                if(ret == 0)
                {
                    strcpy(file_name[name_index], p1);

                    name_index ++;
                }
            }

        }
        closedir(path);
    } else
        printf(">>error occur while get data file name\n");

    //printf("||FileName end\n");
    return name_index;
}



