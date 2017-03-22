#include <stdlib.h>
#include <string.h>


char* getNextLevel(char** level, char* path)
{
    *level = malloc(sizeof(char) * 200);
    int l = 0;
    (*level)[l++] = *path++;
    for (; *path == '/'; path++);
    for (; *path != '/' && *path != '\0'; path++)
        (*level)[l++] = *path;
    (*level)[l] = '\0';
    return path;
}
char* goLower(char* tail, char* level)
{
    while ((*tail++ = *level++) != '\0');
    return tail - 1;
}
char* goUpper(char* head, char* tail)
{
    for (; *tail != '/' && tail != head; tail--);
    if (tail == head) {
        *head = '/';
        tail++;
    }
    *tail = '\0';
    return tail;
}

char* simplifyPath(char* path)
{
    int sz=strlen(path);
    char* head = malloc(sz);
    memset(head,0,sz);
    char* tail = head;
    char* level;
    *tail++ = '/';
    while (*path != '\0') {
        path = getNextLevel(&level, path);
        if (strcmp(level, "/.") == 0 || strcmp(level, "/") == 0)
            continue;
        else if (strcmp(level, "/..") == 0)
            tail = goUpper(head, tail);
        else
            tail = goLower(tail, level);
        free(level);
    }
    while (*(head+1) == '/') head++;
    return head;
}




