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