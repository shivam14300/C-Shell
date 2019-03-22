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

int bgNf(int background,char **tokens)
{
    if(!strcmp(tokens[position-1],"&"))
    {
        tokens[position-1] = NULL;
        background = 1;
    }
    int status;
    pid_t pid;
    pid = fork();
    if(pid < 0)return 0;
    else if(pid == 0)
        if(execvp(tokens[0],tokens)<0)
            return 0;
    if(background == 0)
        (void)waitpid(pid,NULL,0);
    else if(background == 1)
        strcpy(process_name[pid],tokens[0]);
}



void handler(int sig)
{
    pid_t pid;
    int i,status;
    for(i=0;i<4000005;i++)
    {
        if(strcmp(process_name[i],"\0"))
        {
            if(waitpid(i,&status,WNOHANG))
            {
                printf("\n%s with pid %d exited normally.(Press enter to Continue)\n",process_name[pid], pid);
                strcpy(process_name[i],"\0");
            }
        }
    }
}
