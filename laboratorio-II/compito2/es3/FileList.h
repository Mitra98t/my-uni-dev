#include <time.h>

typedef struct VersionList
{
    int version;
    time_t timestamp;
    struct VersionList *next;
} VersionList;

typedef struct FileList
{
    char *name;
    VersionList *versions;
    struct FileList *next;
} FileList;

FileList *searchFile(FileList *, const char *);

int addFile(FileList *, const char *);
int addVersion(FileList *, const char *, int, time_t);

void stampaTMP(FileList *);