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


void cmdJOBS()
{
    int i;
    for(i=0;i<4000005;i++)
    {
        if(!strcmp(process_name[i],""))
        {
            continue;
        }
        else
        {
            char temp[1024],St[100];
            int error_number[3];
            strcpy(temp, "/proc/");

            if(i)
                sprintf(temp,"/proc/%d",i);
            strcpy(St, temp);
            strcat(St, "/stat");
            
            error_number[0] = 0;
            FILE * stat = fopen(St, "r");
            if(stat == NULL)
            {
                printf("No such pid\n");
                return;
            }
            if(error_number[0]) {
                fprintf(stderr, "Error reading %s: %s\n", St, strerror(error_number[0]));
                return;
            }

            int pid; 
            char status; 
            char name[20];
            fscanf(stat, "%d", &pid); 
            fscanf(stat, "%s", name); 
            fscanf(stat, " %c", &status);

            if(status == 'S')
                printf("Running ");
            else if(status == 'T')
                printf("Stopped ");
            fclose(stat);
            
            printf("%s [%d]\n",process_name[i],i);
        }
    }
    return;
}
void cmdKJOB(char **toks)
{
    if(toks[2] == NULL)printf("Too few args\n");
    if(toks[3] != NULL)printf("Too many args\n");
    int i;
    int n = atoi(toks[1]);
    int n1 = 0;
    int sig = atoi(toks[2]); 
    printf("%d\n",n);
    printf("%d\n",sig);
    for(i=1;i<4000005;i++)
    {
        if(strcmp(process_name[i],"\0"))
        {
            n1++;
            if(n1==n)
            {
                printf("%d\n",i);
                kill(i,sig);
                return;
            }
        }
    }
}
void cmdSETENV(char **toks)
{
    int count = 0,i=0;
    while(toks[i] != NULL)
    {
        count++;
        i++;
    }
    if(count > 3)printf("To many Args...\n");
    else if(count <2)printf("Less Args given...\n");
    else if(count == 2)setenv(toks[1]," ",2);
    else if(count == 3)setenv(toks[1],toks[2],2);
}
void cmdUNSETENV(char **toks)
{
    int count = 0,i=0;
    while(toks[i] != NULL)
    {
        count++;
        i++;
    }
    if(count == 1)printf("Less args given...\n");
    else unsetenv(toks[1]);
}
void cmdOVERKILL()
{
    int i;
    for(i=0;i<4000005;i++)
    {
        if(strcmp(process_name[i],""))
        {   
            kill(i,9);
            strcpy(process_name[i],"");
        }
    }
}
void cmdFG(char **toks)
{
    if(toks[1] == NULL)printf("Too few args\n");
    if(toks[2] != NULL)printf("Too many args\n");
    int i;
    int n = atoi(toks[1]);
    for(i=0;i<4000005;i++)
    {
        if(strcmp(process_name[i],"\0"))
        {
            n--;
            if(n == 0)
            {
                printf("%s in fg\n",process_name[i]);
                kill(i,SIGCONT);
                waitpid(i,NULL,0);
            }
        }
    }
}
void cmdBG(char **toks)
{
    if(toks[1] == NULL)printf("Too few args\n");
    if(toks[2] != NULL)printf("Too many args\n");
    int i;
    int n = atoi(toks[1]);
    for(i=0;i<4000005;i++)
    {
        if(strcmp(process_name[i],"\0"))
        {
            n--;
            if(n == 0)
            {
                kill(i,SIGCONT);
            }
        }
    }
}