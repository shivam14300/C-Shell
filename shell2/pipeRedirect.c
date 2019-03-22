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

void pipes(char **toks)
{
    int fd1[2],fd2[2],n=1,i,j=0,flag=0,k;
    char *cmd[1024];
    pid_t pid; 
    
    for(i=0;toks[i]!='\0';i++)if(!strcmp(toks[i],"|"))n++;
    
    i = 0;
    int flag1 = 0;
    int redrt = 0;
    int in = 0;
    char inputfile[64];
    char *inpcmd[1024];
    while(toks[j]!=NULL && flag == 0)
    {
        k=0;
        redrt = 0;
        in = 0;
        while(strcmp(toks[j],"|"))
        {
            if(strcmp(toks[i],">") || strcmp(toks[i],"<") || strcmp(toks[i],">>"))
            {
                redrt = 1;
                if (toks[i][0] == '<')
                {
                    in = 1;
                    flag1 = 1;
                    strcpy(inputfile,toks[i+1]);
                }
            }
            cmd[k] = toks[j];
            if(flag1 == 0)
                inpcmd[k] = toks[j];
            j++;
            k++;
            if(toks[j] == NULL)
            {
                flag = 1;
                break;
            }
        }
        j++;
        cmd[k] = NULL;

        if(i%2)pipe(fd1);
        else pipe(fd2);

        pid = fork();

        if(pid==-1)
        {
            if(i != n-1)
            {
                if(i%2)close(fd1[1]);
                else close(fd2[1]);
            } 
            printf("Child process error\n");
            return;  
        }
        else if(pid == 0)
        {
            if(i==0 && redrt == 1 && in == 1)
            {
                fd2[1] = open(inputfile,O_RDONLY,0);
                dup2(fd2[1],STDIN_FILENO);
                execvp(inpcmd[0],inpcmd);
                close(fd2[1]);

            }
            else if(i==n-1 && redrt == 1)
            {
                if(n%2)dup2(fd1[0],STDIN_FILENO);
                else dup2(fd2[0],STDIN_FILENO);
                redirect(cmd);
            }
            else
            {
                if(i==0) dup2(fd2[1],STDOUT_FILENO);
                else if(i == n-1)
                {
                    if(n%2)dup2(fd1[0],STDIN_FILENO);
                    else dup2(fd2[0],STDIN_FILENO);
                }   
                else
                {
                    if(i%2)
                    {
                        dup2(fd2[0],STDIN_FILENO);
                        dup2(fd1[1],STDOUT_FILENO);
                    }
                    else
                    {
                        dup2(fd1[0],STDIN_FILENO);
                        dup2(fd2[1],STDOUT_FILENO);
                    }
                }
                if(execvp(cmd[0],cmd) == -1)
                {
                    kill(getpid(),SIGTERM);
                }
            }
 
        }
        if(i==0) close(fd2[1]);
        else if(i == n-1)
        {
            if(n%2)close(fd1[0]);
            else close(fd2[0]);
        }   
        else
        {
            if(i%2)
            {
                close(fd2[0]);
                close(fd1[1]);
            }
            else
            {
                close(fd1[0]);
                close(fd2[1]);
            }
        }
        waitpid(pid,NULL,0);
        i++;
    }

}
void redirect(char ** args)
{
    pid_t pid, status,wpid;
    
    pid = fork();
    
    if(pid == 0) 
    {
        int idx = 0;
        int fd;
        int i;
        int in = 0;
        int out = 0;
        int app = 0;
        char inputs[64];
        char outputs[16][64];
        char appends[16][64];
        for(i=0;args[i]!='\0';i++) 
        {   
            if (args[i][0] == '>' && args[i][1] != '>') 
            {
                args[i] = NULL;
                strcpy(outputs[out++],args[i+1]);
            }
            else if (args[i][0] == '<') 
            {
                args[i] = NULL;
                strcpy(inputs, args[i+1]);
                in = 1;
            }
            else if(args[i][0] == '>' && args[i][1] == '>')
            {
                args[i] = NULL;
                strcpy(appends[app++],args[i+1]);
            }
            idx++;
        }
        if(in==1)
        { 
            fd = open(inputs, O_RDONLY, 0);
            if(fd<0)
                perror("Error in opening the file");
            if(dup2(fd,0) < 0) 
                ("Error in input dup2");
            close(fd);
        }
        if(out > 0)
        {
            for (i=0;i<out;i++)
            {
                fd = open(outputs[i], O_WRONLY | O_TRUNC | O_CREAT ,0644);
                if(fd<0)
                    perror("Error opening output file");
                if(dup2(fd,STDOUT_FILENO)<0)
                    perror("Error - output duping");
                close(fd);
            }
        }
        if(app > 0)
        {
            for (i=0;i<app;i++)
            {
                fd = open(appends[i], O_WRONLY | O_APPEND, 0644);
                if(fd<0)
                    perror("Error opening the output(append) file");
                if(dup2(fd,STDOUT_FILENO)<0)
                    perror("Error - output(append) duping");
                close(fd);
            }
        }
        if (execvp (args[0], args) == -1) 
            perror ("execvp");
        _exit (EXIT_FAILURE);   
    }
    else if (pid < 0) 
    {
        perror ("fork");
    }
    else if (pid > 0) 
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }        
}