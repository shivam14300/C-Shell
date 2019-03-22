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

void cmdPWD()
{
    char path[1024];
    getcwd(path,sizeof(path));
    int i;
    for(i=0;path[i]!='\0';i++)printf("%c",path[i]);
    printf("\n");
}