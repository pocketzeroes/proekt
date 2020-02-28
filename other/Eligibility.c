#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
    int num;
    scanf("%d", &num);
    for(int i=0; i<num; i++){
        char*name  =getstr();
        char*school=getstr();
        char*age   =getstr();
        int courses;
        scanf("%d", &courses);
        bool elgible = true;
        printf("%s ", name);
        if(strcmp(school, "2010/00/00")>=0){
            puts("eligible");
            continue;
        }
        if(strcmp(age, "1991/00/00")>=0){
            puts("eligible");
            continue;
        }
        if(courses > 40){
            puts("ineligible");
            continue;
        }
        puts("coach petitions");
    }
    return 0;
}
