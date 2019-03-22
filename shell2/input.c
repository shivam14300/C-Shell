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

void cmds(char **tokens)
{
    if(!strcmp(tokens[0],"cd"))cmdCD(tokens,originalPath);
    else if(!strcmp(tokens[0],"pwd"))cmdPWD();
    else if(!strcmp(tokens[0],"echo"))cmdECHO(tokens);
    else if(!strcmp(tokens[0],"ls"))cmdLS(tokens);
    else if(!strcmp(tokens[0],"pinfo"))cmdPINFO(tokens);
    else if(!strcmp(tokens[0],"remindme"))cmdREMINDME(tokens);
    else if(!strcmp(tokens[0],"clock"))cmdCLOCK(tokens);
    else if(!strcmp(tokens[0],"setenv"))cmdSETENV(tokens);
    else if(!strcmp(tokens[0],"unsetenv"))cmdUNSETENV(tokens);
    else if(!strcmp(tokens[0],"jobs"))cmdJOBS(tokens);
    else if(!strcmp(tokens[0],"kjob"))cmdKJOB(tokens);
    else if(!strcmp(tokens[0],"bg"))cmdBG(tokens);
    else if(!strcmp(tokens[0],"fg"))cmdFG(tokens);
    else if(!strcmp(tokens[0],"overkill"))cmdOVERKILL();
    else if(!strcmp(tokens[0],"exit") || !strcmp(tokens[0],"quit"))exit(0);
    else bgNf(0,tokens);
}

char **split_cmd(char *line,char* delim)
{
    int bufsize = 64;
    position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    if (!tokens) 
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, delim);
    while (token != NULL) 
    {
        tokens[position] = token;
        position++;
        if (position >= bufsize) 
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) 
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, delim);
    }
    tokens[position] = NULL;
    return tokens;
}

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