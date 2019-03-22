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
#include<fcntl.h>
#include "header.h"

void cmdCD(char **tokens,char originalPath[])
{
    if(tokens[1] == NULL)chdir(originalPath);
    else if(!strcmp(tokens[1],"~")) chdir(originalPath);
    else if(chdir(tokens[1]) < 0) printf("cd: no such file or directory: %s\n",tokens[1]);
    else chdir(tokens[1]);
}



void cmdECHO(char** tokens)
{
    int i;
    for(i=1;tokens[i]!=NULL;i++)
        printf("%s ",tokens[i]);
    printf("\n");
}
int cmdPINFO(char ** toks) 
{
    char temp[1024],St[100],VM[100],EP[100];
    int error_number[3];

//-------------------------------------------------------------------------

    int pid; 
    char status; 
   
    strcpy(temp, "/proc/");
    if(toks[1])
        strcat(temp, toks[1]);
    else 
        strcat(temp, "self");

    strcpy(St, temp);
    strcat(St, "/stat");
    
    error_number[0] = 0;
    FILE * st = fopen(St, "r");
    
    if(st == NULL)
    {
        printf("No such pid\n");
        return 1;
    }
    fscanf(st, "%d", &pid); 
    fscanf(st, " %c", &status);
    printf( "pid -- %d\n", pid);
    printf( "Procs Status -- %c\n", status);
    fclose(st);

//-------------------------------------------------------------------------    

    error_number[0] = 0;
    strcpy(VM, temp); 
    strcat(VM, "/statm");
    FILE * mem = fopen(VM, "r");
    
    if(error_number[0])     
    {
        fprintf(stderr, "Error reading %s: %s\n", VM, strerror(error_number[0]));
            return 1;
    }
    int memSize; 
    fscanf(mem, "%d", &memSize);
    fprintf(stdout, "Virtual Memory -- %d\n", memSize);
    fclose(mem);

//-------------------------------------------------------------------------

    error_number[0] = 0;
    char relPath[1000];
    char exePath[1000];
    strcpy(EP, temp); 
    strcat(EP, "/exe");
    readlink(EP, exePath, sizeof(exePath));
    if(error_number[0]) 
    {
        fprintf(stderr, "Error %s: %s\n", EP, strerror(error_number[0]));
        return 1;
    }

    int i = 0, baseL = strlen(originalPath);
    
    for(i = 0; i < baseL; i++)
        if(originalPath[i] != exePath[i]) 
            break;
    
    if(i == baseL) 
    {
        relPath[0] = '~'; relPath[1] = '\0';
        strcat(relPath, (const char *)&exePath[baseL]);
    }
    else 
    {
        strcpy(relPath, exePath);
        relPath[strlen(exePath)] = '\0';
    }

    i = 0;
    while(exePath[i]) exePath[i++] = '\0';
    
    fprintf(stdout, "Executable Path -- %s\n", relPath);
    return 1;
}

void cmdPWD()
{
    char path[1024];
    getcwd(path,sizeof(path));
    int i;
    for(i=0;path[i]!='\0';i++)printf("%c",path[i]);
    printf("\n");
}
void getpath(char originalPath[])
{
    char path[1024];
    getcwd(path,sizeof(path));
    if(strlen(originalPath) > strlen(path))
    {
        printf("%s",path);
        return;
    }
    int i=0,k;
    for(i=0;originalPath[i]!='\0';i++)if(originalPath[i]!=path[i])break;
    for(k=i;path[k]!='\0';k++)printf("%c",path[k]);
}