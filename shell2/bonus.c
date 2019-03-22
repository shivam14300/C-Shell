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

void cmdREMINDME(char **tokens)
{
    pid_t pid;
    pid = fork();
    int i = 2;
    if(pid == 0)
    {
        sleep(atoi(tokens[1]));
        printf("\nReminder: ");
        while(tokens[i] != NULL)
        {
            printf("%s ",tokens[i]);
            i++;
        }
        exit(1);
    }
    if(pid < 0)
    {
        fprintf(stderr, "forking error\n");
    }
}

void cmdCLOCK(char **tokens)
{
    int n = atoi(tokens[4])/atoi(tokens[2]);
    char path[1024];
    char buffer[1024];
    char buffer1[1024];
    long long int length;
    strcpy(path,"/proc/driver/rtc");
    int error = 0;
    while(n--)
    {
        FILE * f = fopen(path,"r");
        if(error)
        {
            fprintf(stderr,"Error reading %s: %s\n",path,strerror(error));
            return;
        }
        if(f)
        {
            fscanf(f,"%*s %*s %s",buffer);
            fscanf(f,"%*s %*s %s",buffer1);
            printf("%s ",buffer1);
            printf("%s \n",buffer);
            sleep(atoi(tokens[2]));
        }
        fclose(f);
    }
}