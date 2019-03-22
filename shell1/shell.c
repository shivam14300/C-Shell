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

int main()
{
    char input[1024]; 
    struct passwd *pass;
    pass = getpwuid(getuid()); 
    name = pass->pw_name;
    getcwd(originalPath,sizeof(originalPath));
    int result; 
    result = gethostname(hostname,100);
    if(result)
    {
        perror("gethostname");
        return EXIT_FAILURE;
    }
    if(result<0)
    {
        perror("printf");
        return EXIT_FAILURE;
    }
    while(1)
    {
        printf("<%s @ %s:~",name,hostname);
        getpath(originalPath);
        if (takeInput(input)) continue;
        char ** tokens = split_cmd(input,semiColon);
        int i;
        for(i=0;tokens[i]!=NULL;i++)
        {
            char ** toks = split_cmd(tokens[i],LSH_TOK_DELIM);
            if(toks[0]!=NULL) cmds(toks);
            else continue;
        }
        signal(SIGCHLD, handler);
    }
    return EXIT_SUCCESS;
}