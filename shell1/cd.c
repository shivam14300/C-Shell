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

void cmdCD(char **tokens,char originalPath[])
{
    if(tokens[1] == NULL)chdir(originalPath);
    else if(!strcmp(tokens[1],"~")) chdir(originalPath);
    else if(chdir(tokens[1]) < 0) printf("cd: no such file or directory: %s\n",tokens[1]);
    else chdir(tokens[1]);
}