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

VersionList searchVers(VersionList vl, int v)
{
    VersionNode *iterator = vl;

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

    VersionNode *tmp = (VersionNode *)malloc(sizeof(VersionNode));
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
        VersionNode *vIter = iter->versions;
        while (vIter != NULL)
        {
            printf("| Vers: %d - Time: %s |", vIter->version, vIter->timestamp);
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

void removeVersionList(VersionNode *vl)
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

    VersionNode *vIter = foundF->versions;
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
            VersionNode *old = vIter->next;
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
    if (!found)
        return NULL;
    VersionList v = (found->versions);
    return v;
}

FileList loadFileList(const char *file)
{
    FileList fl = NULL;
    FILE *in = fopen((char *)file, "r");
    if (!in)
        return NULL;

    char line[1000];

    while (!feof(in))
    {
        fgets(line, 1000, in);
        char *name = strtok(line, ":");
        if (addFile(&fl, name))
            return NULL;
        char *token = NULL;

        while ((token = strtok(NULL, ";")))
        {
            char numC[2] = {token[0], '\0'};
            int num = atoi(numC);
            if (!num)
                return NULL;
            char *time = cleanstr(strdup(&token[2]));
            addVersion(&fl, name, num, (time_t)time);
            // if (addVersion(&fl, name, num, time))
            //     return NULL;
        }
    }

    return fl;
}

int saveFileList(FileList f, const char *file)
{
    FileNode *tmp = NULL;
    while (f != NULL)
    {
        FileNode *fn = (FileNode *)malloc(sizeof(FileNode));
        fn->name = f->name;
        fn->versions = f->versions;
        fn->next = tmp;
        tmp = fn;
        f = f->next;
    }

    FileNode *iter = tmp;
    char buff[1000];
    char *str = (char *)malloc(1000);
    strcat(str, "_");
    while (iter != NULL)
    {
        sprintf(buff, "%s:%s", iter->name, getVersString(iter->versions));
        strcat(str, buff);
        iter = iter->next;
    }

    strtok(str, "_");

    // printf("%s", strtok(NULL, "\0"));

    FILE *out = fopen(file, "w");
    if (!out)
        return 1;

    fprintf(out, "%s", strtok(NULL, "\0"));

    if (ferror(out))
        return 1;

    fclose(out);
    return 0;
}

char *getVersString(VersionList v)
{
    VersionNode *tmp = NULL;
    while (v != NULL)
    {
        VersionNode *vn = (VersionNode *)malloc(sizeof(VersionNode));
        vn->version = v->version;
        vn->timestamp = v->timestamp;
        vn->next = tmp;
        tmp = vn;
        v = v->next;
    }

    VersionNode *iter = tmp;
    char buff[1000];
    char *str = (char *)malloc(1000);

    strcat(str, "/");

    while (iter != NULL)
    {
        sprintf(buff, "%d,%s", iter->version, (char *)iter->timestamp);
        strcat(str, buff);
        if (iter->next != NULL)
            strcat(str, ";");
        iter = iter->next;
    }
    strcat(str, "\n\0");
    strtok(str, "/");
    return strtok(NULL, "\0");
}

char *cleanstr(char *s)
{
    if (s[strlen(s) - 1] == '\n')
        s[strlen(s) - 1] = '\0';

    // for (int i = 0; i < strlen(s); i++)
    // {
    //     if (s[i] == '\n')
    //         s[i] = '\0';
    // }

    return s;
}