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