#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


void read_file(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        return;
    }

    fclose(file);
}


int get_files_count(DIR *dir, const char *dir_path)
{
    struct dirent *ent;
    struct stat filestat;

    int count = 0;
    while ((ent = readdir(dir)) != NULL) 
    {
        if (strcmp(ent->d_name, ".") == 0 ||
            strcmp(ent->d_name, "..") == 0)
        {
            continue;
        }
                
        if (stat(ent->d_name,&filestat) == -1) 
        {
            perror("Error while getting file information");
            continue;
        }

        if (!S_ISDIR(filestat.st_mode))
        {
            count++;
        }
    }
    
    return count;
}


char** read_directory(const char *dir_path, int *num_files)
{
    DIR *dir;
    struct dirent *ent;
    struct stat filestat;
   
    if ((dir = opendir(dir_path)) == NULL) 
    {
        perror("Error while reading directory");
        return NULL;        
    }

    int count = get_files_count(dir, dir_path);
    char **file_paths = (char **)malloc(count * sizeof(char *));
    if (file_paths == NULL) 
    {
        perror("Memory allocation error");
        closedir(dir);
        return NULL;
    }

    rewinddir(dir);
    int index = 0;
    while ((ent = readdir(dir)) != NULL) 
    {
        if (strcmp(ent->d_name, ".") == 0 ||
            strcmp(ent->d_name, "..") == 0)
        {
            continue;
        }
        
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, ent->d_name);
        
        stat(ent->d_name, &filestat);

        if (!S_ISDIR(filestat.st_mode)) 
        {
            file_paths[index] = strdup(full_path);
            index++;
        }
    }

    closedir(dir);

    *num_files = count;
    return file_paths;
}
