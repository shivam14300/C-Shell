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

void cmdLS(char **tokens)
{
    struct dirent *d;
    DIR* p;
    if(tokens[1] != NULL && !strcmp(tokens[1],"-a"))
    {
        if(tokens[2] != NULL)p = opendir(tokens[2]);
        else p = opendir(".");
        if( p == NULL )
        {
            perror("Cannot find directory");
            return;
        }
        while(d = readdir(p)) printf("%s  ",d->d_name);
        printf("\n");
    }
    else if(tokens[1] != NULL && !strcmp(tokens[1],"-l"))
    {
        struct dirent* current_directory;
        struct stat my_stat;
        struct tm lt;  
        struct passwd *pwd; // For User-ID
        DIR* directory;

        if(tokens[2] != NULL) directory = opendir(tokens[2]);
        else directory = opendir(".");

        if(directory == NULL)
        { 
            printf("list_dir : %s : %s \n", tokens[2], strerror(errno));
            return;
        }   
        while( (current_directory = readdir(directory) ) )     
        {
            if ( current_directory->d_name[0] != '.')
            {
                struct stat my_stat = {0};
                stat(current_directory->d_name, &my_stat);  
                struct group *group;
                group=getgrgid(my_stat.st_gid);
                if ( (stat(current_directory->d_name, &my_stat) ) == 0 )    
                {
                    pwd = getpwuid(my_stat.st_uid); // Get User-ID
                }
                printf( (S_ISDIR(my_stat.st_mode)) ? "d" : "-");
                printf( (my_stat.st_mode & S_IRUSR) ? "r" : "-");
                printf( (my_stat.st_mode & S_IWUSR) ? "w" : "-");
                printf( (my_stat.st_mode & S_IXUSR) ? "x" : "-");
                printf( (my_stat.st_mode & S_IRGRP) ? "r" : "-");
                printf( (my_stat.st_mode & S_IWGRP) ? "w" : "-");
                printf( (my_stat.st_mode & S_IXGRP) ? "x" : "-");
                printf( (my_stat.st_mode & S_IROTH) ? "r" : "-");
                printf( (my_stat.st_mode & S_IWOTH) ? "w" : "-");
                printf( (my_stat.st_mode & S_IXOTH) ? "x" : "-");
                // Last Modified 
                time_t t = my_stat.st_mtime;
                localtime_r(&t, &lt);
                char timebuf[80];
                strftime(timebuf, sizeof(timebuf), "%b %d %H:%M ", &lt);
                if (pwd != 0) 
                {
                    printf(" %ld  %s \t %s \t %ld \t %s \t %s\n",my_stat.st_nlink,group->gr_name, pwd->pw_name, (long)my_stat.st_size, timebuf, current_directory->d_name);
                } 
                else  
                {
                    printf(" %ld  %s \t %ld \t %s \t %s\n",my_stat.st_nlink,group->gr_name, (long)my_stat.st_size, timebuf, current_directory->d_name);
                }
            }
        }
        closedir(directory);        
    }
    else if(tokens[1] != NULL && !strcmp(tokens[1],"-al") || tokens[1] != NULL && !strcmp(tokens[1],"-la") || tokens[1] != NULL && !strcmp(tokens[1],"-l") && tokens[2] != NULL && !strcmp(tokens[2],"-a") || tokens[1] != NULL && !strcmp(tokens[1],"-a") && tokens[2] != NULL && !strcmp(tokens[2],"-l"))
    {
        struct dirent* current_directory;
        struct stat my_stat;
        struct tm lt;  
        struct passwd *pwd; // For User-ID
        DIR* directory;
        directory = opendir(".");
        if(directory == NULL)
        { 
            printf("list_dir : %s : %s \n", tokens[2], strerror(errno));
            return;
        }   
        while( (current_directory = readdir(directory) ) )     
        {
            struct stat my_stat = {0};
            stat(current_directory->d_name, &my_stat);  
            struct group *group;
            group=getgrgid(my_stat.st_gid);
            if ( (stat(current_directory->d_name, &my_stat) ) == 0 )    
            {
                pwd = getpwuid(my_stat.st_uid); // Get User-ID
            }
            printf( (S_ISDIR(my_stat.st_mode)) ? "d" : "-");
            printf( (my_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (my_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (my_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (my_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (my_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (my_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (my_stat.st_mode & S_IROTH) ? "r" : "-");
            printf( (my_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (my_stat.st_mode & S_IXOTH) ? "x" : "-");
            // Last Modified 
            time_t t = my_stat.st_mtime;
            localtime_r(&t, &lt);
            char timebuf[80];
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M ", &lt);
            if (pwd != 0) 
            {
                printf(" %ld  %s \t %s \t %ld \t %s \t %s\n",my_stat.st_nlink,group->gr_name, pwd->pw_name, (long)my_stat.st_size, timebuf, current_directory->d_name);
            } 
            else  
            {
                printf(" %ld  %s \t %ld \t %s \t %s\n",my_stat.st_nlink,group->gr_name, (long)my_stat.st_size, timebuf, current_directory->d_name);
            }
        }
        closedir(directory);        
    }
    else
    {
        if(tokens[1] != NULL)
            p = opendir(tokens[1]);
        else
            p = opendir(".");
        if( p == NULL )
        {
            perror("Cannot find directory");
            return;
        }
    
        while(d = readdir(p))
            if ( d->d_name[0] != '.')
                printf("%s  ",d->d_name);
        printf("\n");
    }
}
