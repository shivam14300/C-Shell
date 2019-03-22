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