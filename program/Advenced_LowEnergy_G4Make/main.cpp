#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "BuildG4Proj.h"
#include "Constant.h"
#include "CreateFile.h"
#include "MakeDir.h"

int max_energy;
int number_of_proj;


int main(void)
{
    printf(">>make Geant4 project\n");
    printf("||enter the maximum energy of particle\n>> ");
    fflush(stdin);
    scanf("%d", &max_energy);

    chdir(ProjectDir);
    system("rm -rf e-");
    system("rm -rf mu-"); 
    system("rm -rf proton");
    number_of_proj = max_energy * divide;

    printf("||number of project: %d\n", number_of_proj);  
    MakeDir(number_of_proj);
    MakeFile(number_of_proj);
    Build(number_of_proj);
}
    