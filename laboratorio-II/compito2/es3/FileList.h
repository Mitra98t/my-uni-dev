#include <time.h>

typedef struct VersionNode
{
    int version;
    time_t timestamp;
    struct VersionNode *next;
} VersionNode;
typedef VersionNode *VersionList;

typedef struct FileNode
{
    char *name;
    VersionList versions;
    struct FileNode *next;
} FileNode;
typedef FileNode *FileList;

FileNode *searchFile(FileList, const char *);
VersionList searchVers(VersionList, int);

int addFile(FileList *, const char *);
int addVersion(FileList *, const char *, int, time_t);

int removeFile(FileList *, const char *);
void removeVersionList(VersionNode *);
int removeVersion(FileList *, const char *, int);
void freeFileList(FileList *);
void removeFileList(FileNode *fn);

VersionList getHist(FileList, const char *);

FileList loadFileList(const char *);
int saveFileList(FileList, const char *);
char *getVersString(VersionList);

void stampaTMP(FileList);
char *cleanstr(char *);