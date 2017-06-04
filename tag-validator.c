#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include <ctype.h>

char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

void content(const char**p);

bool cdata(const char** p) {
    const char* prefix = "<![CDATA[";
    if (strncmp(*p, prefix, strlen(prefix)) != 0) {
        return false;
    }
    const char* q = strstr(*p, "]]>");
    if (q == NULL) {
        return false;
    } else {
        *p = q + 3;
        return true;
    }
}

bool tag(const char** p) {
    const char* q = *p;
    if (*q++ != '<') {
        return false;
    }
    char*tag=strdup("");
    while (*q != '\0' && isupper(*q)) {
        tag = concat(tag, *q);
        ++q;
    }
    int tag_length = strlen(tag);
    if (tag_length < 1 || tag_length > 9) {
        return false;
    }
    if (*q++ != '>') {
        return false;
    }
    content(&q);
    if (*q++ != '<') {
        return false;
    }
    if (*q++ != '/') {
        return false;
    }
    if (strncmp(q, tag, tag_length) != 0) {
        return false;
    } else {
        q += tag_length;
    }
    if (*q++ != '>') {
        return false;
    }
   *p = q;
    return true;
}

void content(const char**p) {
    while (*p[0] != '\0') {
        if (*p[0] != '<') {
            ++(*p);
        } else if (!cdata(p) && !tag(p)) {
            break;
        }
    }
}

bool isValid(const char*code) {
    const char* p = code;
    return tag(&p) && *p == '\0';
}


#ifdef _WIN32
int main(){
    puts(isValid( "<DIV>This is the first line <![CDATA[<div>]]></DIV>" ) ? "yes" : "no" );
}
#endif
































