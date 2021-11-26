#include <time.h>

typedef struct VersionList
{
    int version;
    time_t timestamp;
    struct VersionList *next;
} VersionList;

typedef struct FileNode
{
    char *name;
    VersionList *versions;
    struct FileNode *next;
} FileNode;
typedef FileNode *FileList;

FileNode *searchFile(FileList, const char *);

int addFile(FileList *, const char *);
int addVersion(FileList *, const char *, int, time_t);

void stampaTMP(FileList);