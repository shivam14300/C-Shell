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

void cmds(char **tokens)
{
    if(!strcmp(tokens[0],"cd"))cmdCD(tokens,originalPath);
    else if(!strcmp(tokens[0],"pwd"))cmdPWD();
    else if(!strcmp(tokens[0],"echo"))cmdECHO(tokens);
    else if(!strcmp(tokens[0],"ls"))cmdLS(tokens);
    else if(!strcmp(tokens[0],"pinfo"))cmdPINFO(tokens);
    else if(!strcmp(tokens[0],"remindme"))cmdREMINDME(tokens);
    else if(!strcmp(tokens[0],"clock"))cmdCLOCK(tokens);
    else if(!strcmp(tokens[0],"exit") || !strcmp(tokens[0],"quit"))exit(0);
    else bgNf(0,tokens);
}