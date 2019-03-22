#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<string.h>
#include<dirent.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<grp.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include "header.h"

int cmdPINFO(char ** tokens) 
{
    char Procs[1024];
    strcpy(Procs, "/proc/");

    if(tokens[1])strcat(Procs, tokens[1]);
    else strcat(Procs, "self");
    
    char Stats[100];
    strcpy(Stats, Procs);
    strcat(Stats, "/stat");
    
    int error_number[3];
    error_number[0] = 0;
    FILE * stat = fopen(Stats, "r");
    if(stat == NULL)
    {
        printf("No such pid\n");
        return 1;
    }
    if(error_number[0]) {
        fprintf(stderr, "Error reading %s: %s\n", Stats, strerror(error_number[0]));
        return 1;
    }

    int pid; char status; char name[20];
    fscanf(stat, "%d", &pid); fscanf(stat, "%s", name); fscanf(stat, " %c", &status);
    printf( "pid -- %d\n", pid);
    printf( "Procs Status -- %c\n", status);
    fclose(stat);
    
    error_number[0] = 0;
    strcpy(Stats, Procs); strcat(Stats, "/statm");
    FILE * mem = fopen(Stats, "r");
    
    if(error_number[0])     {
	fprintf(stderr, "Error reading %s: %s\n", Stats, strerror(error_number[0]));
        return 1;
    }
    int memSize; fscanf(mem, "%d", &memSize);
    fprintf(stdout, "Virtual Memory -- %d\n", memSize);
    fclose(mem);
    char exePath[1000];
    strcpy(Stats, Procs); strcat(Stats, "/exe");
    error_number[0] = 0;

    readlink(Stats, exePath, sizeof(exePath));
    if(error_number[0]) {
        fprintf(stderr, "Error reading symbolic link %s: %s\n", Stats, strerror(error_number[0]));
        return 1;
    }

    int sameChars = 0, baseL = strlen(originalPath);
    for(sameChars = 0; sameChars < baseL; sameChars++)
        if(originalPath[sameChars] != exePath[sameChars]) break;;
    
    char relPath[1000];
    if(sameChars == baseL) {
        relPath[0] = '~'; relPath[1] = '\0';
        strcat(relPath, (const char *)&exePath[baseL]);
    }
    else {
        strcpy(relPath, exePath);
        relPath[strlen(exePath)] = '\0';
    }

    int i = 0;
    while(exePath[i]) exePath[i++] = '\0';
    
    fprintf(stdout, "Executable Path -- %s\n", relPath);
    return 1;
}