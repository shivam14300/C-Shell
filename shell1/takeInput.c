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

int takeInput(char* str)
{
    char* buf;
 
    buf = readline("> ");
    if (strlen(buf) != 0) 
    {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } 
    else return 1;
}