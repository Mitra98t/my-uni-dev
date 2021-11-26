#include "FileList.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

FileNode *searchFile(FileList fl, const char *filename)
{
    FileNode *iterator = fl;

    while (iterator != NULL)
    {
        if (iterator->name == filename)
        {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

int addFile(FileList *fl, const char *filename)
{
    // if (searchFile(*fl, filename) != NULL)
    //     return 1;

    FileNode *tmp = (FileNode *)malloc(sizeof(FileNode));
    if (!tmp)
        return 1;
    tmp->name = strdup((char *)filename);
    tmp->versions = NULL;
    tmp->next = *fl;
    *fl = tmp;
    return 0;
}

int addVersion(FileList *fl, const char *filename, int versionID, time_t timestamp)
{
    FileNode *foundF = searchFile(*fl, filename);
    if (!foundF)
    {
        if (!addFile(fl, filename))
        {
            foundF = *fl;
        }
        else
        {
            return 1;
        }
    }

    VersionList *tmp = (VersionList *)malloc(sizeof(VersionList));
    if (!tmp)
        return 1;
    tmp->version = versionID;
    tmp->timestamp = timestamp;
    tmp->next = foundF->versions;
    foundF->versions = tmp;
    return 0;
}

void stampaTMP(FileList fl)
{
    FileNode *iter = fl;
    while (iter != NULL)
    {
        printf("FILE: %s\n", iter->name);
        VersionList *vIter = iter->versions;
        while (vIter != NULL)
        {
            printf("Vers: %d | ", vIter->version);
            vIter = vIter->next;
        }
        printf("\n\n");
        iter = iter->next;
    }
}