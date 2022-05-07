#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

char *findOldestPath(char *);

int timespecCompare(struct timespec, struct timespec);

int main(int argc, char *argv[])
{
    if (argc != 9)
    {
        printf("Missing arguments\n");
        return 1;
    }
    char *dirname = "";
    char *size = "";
    char *warningFactor = "";
    int maxnum;
    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            dirname = argv[i + 1];
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            size = argv[i + 1];
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            warningFactor = argv[i + 1];
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            maxnum = atoi(argv[i + 1]);
        }
    }

    int numberOfFiles = 0;

    struct stat dirStat;
    stat(dirname, &dirStat);

    if (!S_ISDIR(dirStat.st_mode))
    {
        printf("%s is not a directory", dirname);
        return 1;
    }

    // read dir

    DIR *d;
    struct dirent *file;

    if ((d = opendir(dirname)) == NULL)
    {
        perror("opening cwd");
        return 1;
    }

    int dimension = 0;
    // WORK WITH DIR HERE
    struct stat fileStat;
    char *dirBase;
    while ((errno = 0, file = readdir(d)) != NULL)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, ".."))
        {
            dirBase = strdup(dirname);
            stat(strcat(strcat(dirBase, "/"), file->d_name), &fileStat);
            dimension += fileStat.st_size;
            numberOfFiles++;
        }
    }

    if (errno != 0)
    {
        printf("Errore durante la lettura dei file");
        exit(1);
    }

    if ((closedir(d) == -1))
    {
        perror("closing cwd");
        return 1;
    }

    printf("dimensione corrente occupata -> %d\n", dimension);

    int sizeConverted = atoi(size) * 1024 * 1024;
    int remaining = sizeConverted - dimension;
    float warninglvl = sizeConverted * atof(warningFactor);
    int count = 0;
    struct stat fileStatToRem;

    if (maxnum == 0)
        maxnum = numberOfFiles;

    while (remaining < warninglvl && count < maxnum)
    {
        printf("spazio rimanente è minore dello spazio * warning factor quindi devo cancellare qualcosa\n");
        char *fileToRem = findOldestPath(dirname);
        stat(fileToRem, &fileStatToRem);
        int dimensionToRem = fileStatToRem.st_size;
        if (remove(fileToRem) == 0)
        {
            remaining += dimensionToRem;
            printf("Rimosso file %s\n", fileToRem);
            printf("Liberato spazio %d\n", dimensionToRem);
        }
        else
        {
            printf("The file is not deleted.");
            exit(1);
        }
        count++;
    }
    printf("rimossi sufficienti file per rendere lo spazio rimanente maggiore di spazio * warning factor\n");

    return 0;
}

char *findOldestPath(char *dirPath)
{
    struct timespec oldestTime;
    char *oldestPath;
    DIR *d;
    struct dirent *file;
    char *dirBaseOld;
    char *dirBase;
    struct stat fileStatOld;
    struct stat fileStat;

    if ((d = opendir(dirPath)) == NULL)
    {
        perror("opening cwd");
        exit(1);
    }

    while ((errno = 0, file = readdir(d)) != NULL)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, ".."))
        {
            dirBaseOld = strdup(dirPath);
            oldestPath = strcat(strcat(dirBaseOld, "/"), file->d_name);
            stat(oldestPath, &fileStatOld);
            oldestTime = fileStatOld.st_atim;
            break;
        }
    }

    if (errno != 0)
    {
        printf("Errore durante la lettura dei file");
        exit(1);
    }

    if ((closedir(d) == -1))
    {
        perror("closing cwd");
        exit(1);
    }

    if ((d = opendir(dirPath)) == NULL)
    {
        perror("opening cwd");
        exit(1);
    }

    int dimension = 0;
    // WORK WITH DIR HERE

    while ((errno = 0, file = readdir(d)) != NULL)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, ".."))
        {

            dirBase = strdup(dirPath);
            char *dirToStat = strdup("");
            dirToStat = strcat(strcat(dirBase, "/"), file->d_name);
            stat(dirToStat, &fileStat);

            if (timespecCompare(fileStat.st_atim, fileStatOld.st_atim) == 0)
            {
                stat(dirToStat, &fileStatOld);
                oldestPath = dirToStat;
            }
        }
    }

    if (errno != 0)
    {
        printf("Errore durante la lettura dei file");
        exit(1);
    }

    if ((closedir(d) == -1))
    {
        perror("closing cwd");
        exit(1);
    }

    return strdup(oldestPath);
}

int timespecCompare(struct timespec first, struct timespec second)
{
    if (first.tv_sec == second.tv_sec)
    {
        if (first.tv_nsec >= second.tv_nsec)
            return 1;
        else
            return 0;
    }
    if (first.tv_sec >= second.tv_sec)
        return 1;
    else
        return 0;
}