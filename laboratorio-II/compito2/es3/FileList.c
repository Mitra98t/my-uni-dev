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
        if (!strcmp(iterator->name, filename))
        {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

VersionList *searchVers(VersionList *vl, int v)
{
    VersionList *iterator = vl;

    while (iterator != NULL)
    {
        if (iterator->version == v)
        {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

int addFile(FileList *fl, const char *filename)
{
    if (searchFile(*fl, filename) != NULL)
        return 1;

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
    if (foundF == NULL)
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
        printf("\n");
        iter = iter->next;
    }
}

int removeFile(FileList *fl, const char *filename)
{
    FileNode *fIter = *fl;

    if (fIter == NULL)
        return 1;

    if (!strcmp(fIter->name, filename))
    {
        *fl = fIter->next;
        removeVersionList(fIter->versions);
        free(fIter->name);
        free(fIter);
        return 0;
    }

    while (fIter->next != NULL)
    {
        if (!strcmp(fIter->next->name, filename))
        {
            FileNode *old = fIter->next;
            removeVersionList(old->versions);
            fIter->next = old->next;
            free(old->name);
            free(old);
            return 0;
        }
        fIter = fIter->next;
    }

    return 1;
}

void removeVersionList(VersionList *vl)
{
    if (vl != NULL)
    {
        removeVersionList(vl->next);
        free(vl);
    }
}

int removeVersion(FileList *fl, const char *filename, int versionID)
{
    FileNode *foundF = searchFile(*fl, filename);
    if (foundF == NULL)
        return 1;

    // VersionList *foundV = searchVers(foundF->versions, versionID);
    // if (foundV == NULL)
    //     return 2;

    VersionList *vIter = foundF->versions;
    if (vIter == NULL)
        return 2;

    if (vIter->version == versionID)
    {
        foundF->versions = vIter->next;
        free(vIter);
        return 0;
    }

    while (vIter->next != NULL)
    {
        if (vIter->next->version == versionID)
        {
            VersionList *old = vIter->next;
            vIter->next = old->next;
            free(old);
            return 0;
        }
    }

    return 2;
}

void freeFileList(FileList *fl)
{
    removeFileList(*fl);
    *fl = NULL;
}

void removeFileList(FileNode *fn)
{
    if (fn != NULL)
    {
        removeFileList(fn->next);
        removeFile(&fn, fn->name);
    }
}

VersionList getHist(FileList fl, const char *filename)
{
    FileNode *found = searchFile(fl, filename);
    VersionList v = *(found->versions);
    return v;
}