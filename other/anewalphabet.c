#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char*alpha_map[] = {
    "@"        ,
    "8"        ,
    "("        ,
    "|)"       ,
    "3"        ,
    "#"        ,
    "6"        ,
    "[-]"      ,
    "|"        ,
    "_|"       ,
    "|<"       ,
    "1"        ,
    "[]\\/[]"  ,
    "[]\\[]"   ,
    "0"        ,
    "|D"       ,
    "(,)"      ,
    "|Z"       ,
    "$"        ,
    "']['"     ,
    "|_|"      ,
    "\\/"      ,
    "\\/\\/"   ,
    "}{"       ,
    "`/"       ,
    "2"
};
int main(){
    char c;
    while (scanf("%c", &c) > 0) {
        if ('a' <= c && c <= 'z') printf("%s", alpha_map[c - 32 - 'A'] );
        else if ('A' <= c && c <= 'Z') printf("%s", alpha_map[c - 'A'] );
        else printf("%c", c);
    }
    return 0;
}
