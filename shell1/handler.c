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

void handler(int sig)
{
    pid_t pid;
    pid = wait(NULL);
    if(pid > 0)
        printf("\n%s with pid %d exited normally.(Press enter to Continue)\n",process_name[pid], pid);
    else 
        printf("\n%s with pid %d failed to terminate.(Press enter to Continue)\n",process_name[pid], pid);
}