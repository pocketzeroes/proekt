#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    int a;
} FileSystem;
FileSystem*gfs;
int cmpstr(const void*p1, const void*p2)
{
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

char*concat(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s",a,b);
  return ptr;
}
typedef struct FileNodeS{
    bool   IsFolder;
    char*  id;
    char** nodes;
    int    nodesSz;
    char*  content;
}FileNode;
FileNode newFileNode(){
    FileNode rez;
    rez.IsFolder=true;
    rez.id      =strdup("/");
    rez.nodes   =NULL;
    rez.nodesSz =0;
    rez.content =strdup("");
    return rez;
}
FileNode newFileNode2(bool folder, char*mid , char*c){
    FileNode rez;
    rez.IsFolder=folder;
    rez.id      =strdup(mid);
    rez.nodes   =NULL;
    rez.nodesSz =0;
    rez.content =strdup(c);
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
FileNode *pushback(FileNode *array, int *size, FileNode value) {
    FileNode *output = resizeArray(array, FileNode, *size + 1);
    output[(*size)++] = value;
    return output;
}
char**pushbackS(char**array, int *size, char*value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	FileNode*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////

vec f;
FileSystem*fileSystemCreate(){
    f.ptr=pushback(f.ptr,&f.sz,newFileNode());
    return gfs;
}
char** fileSystemLs(FileSystem*fs,char* path, int *retSz){
    char**ss=NULL;
    int   ssSz=0;
    int i, j;
    for(int i=0;i<f.sz;i++){
        FileNode s = f.ptr[i]; 
        if(strcmp(s.id , path)==0){
            if (s.IsFolder){

        #define mss s.nodes
                for (int i = 0; i < s.nodesSz; i++) {
                    int sl = strlen(mss[i]); 
                    for (j = sl - 1; j >= 0; j--) {
                        if (mss[i][j] == '/'){
                            mss[i] += j+1;
                            break;
                        }
                    }
                }
                if(s.nodesSz>1){
//                    puts("sort");
                    qsort(s.nodes, s.nodesSz, sizeof(char*), cmpstr);
  //                  printf("after sort: %s %s\n", s.nodes[0], s.nodes[1]);
                }
               *retSz=s.nodesSz;
                return mss;
            }               
            else {
                char* ss1 = s.id;
                int sl = strlen(ss1);
                for (j = sl - 1; j >= 0; j--) {
                    if (ss1[j] == '/') {
                        ss1 += j+1;
                        break;
                    }
                }
                ss=pushbackS(ss, &ssSz, ss1);
               *retSz=1;
                return ss;
            }
        }
    }        

    return ss;
}
void fileSystemMkdir(FileSystem*fs,char* path) {
    path = concat(path , "/");
    int sl = strlen(path), i, j, last = 0;
    for (i = 1; i < sl; i++){
        if (path[i] == '/'){
            char*s=strdup(path);s[i]='\0';
            for(j = 0; j < f.sz; j++) {
                if(strcmp(f.ptr[j].id , s)==0){
                    last = j;
                    break;
                }
            }
            if (j == f.sz){
//              printf("mkdir %s\n", s);
                f.ptr[last].nodes = pushbackS(f.ptr[last].nodes, &f.ptr[last].nodesSz , s);
                f.ptr=pushback(f.ptr, &f.sz, newFileNode2( true, s, "" ));
                last = f.sz - 1;
            }                   
        }
    }
}
void fileSystemAddContentToFile(FileSystem*fs,char* filePath, char* content) {
    for(int i = 0; i < f.sz; i++)
        if(strcmp(f.ptr[i].id , filePath)==0){
            f.ptr[i].content = concat( f.ptr[i].content, content);
            return;
        }
    filePath = concat( filePath, "/");
    int sl = strlen(filePath), i, j, last = 0;
    for (i = 1; i < sl; i++)
        if (filePath[i] == '/') {
            char*s=strdup(filePath); s[i]='\0';
            for (j = 0; j < f.sz; j++) {
                if(strcmp(f.ptr[j].id, s)==0){
                    last = j;
                    break;
                }
            }
            if (j == f.sz) {
                f.ptr[last].nodes=pushbackS(f.ptr[last].nodes, &f.ptr[last].nodesSz, s);
                f.ptr=pushback(f.ptr, &f.sz, newFileNode2( true, s, content ));
                last = f.sz - 1;
            }
        }
    i = f.sz - 1;
    f.ptr[i].IsFolder = false;
}
char* fileSystemReadContentFromFile(FileSystem*fs,char* filePath) {
    for(int i=0;i<f.sz;i++){FileNode s = f.ptr[i];
        if(strcmp(s.id , filePath)==0)
            return s.content;
    }
    return NULL;
}
void fileSystemFree(FileSystem*fs) {
    f.sz=0;
    if(f.ptr) free(f.ptr);
    f.ptr=NULL;
}

#if _WIN32
int main(){
  FileSystem*obj = fileSystemCreate();
  fileSystemMkdir(obj, "/goowmfn");
  int sz; char**param_1 = fileSystemLs(obj, "/goowmfn", &sz);
  char**param_2 = fileSystemLs(obj, "/", &sz);
  fileSystemMkdir(obj, "/z");
  char**param_3 = fileSystemLs(obj, "/", &sz);
  printf("sz=%d\n", sz);
  printf("%s %s\n", param_3[0], param_3[1] );
  exit(0);
  char**param_4 = fileSystemLs(obj, "/", &sz);
  fileSystemAddContentToFile(obj, "/goowmfn/c","shetopcy");
  char**param_5 = fileSystemLs(obj, "/z", &sz);
  char**param_6 = fileSystemLs(obj, "/goowmfn/c", &sz);
  char**param_7 = fileSystemLs(obj, "/goowmfn"  , &sz);
}
#endif












