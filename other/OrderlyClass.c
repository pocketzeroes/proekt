#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100001];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


int solve(char*A, char*B){
    int lenA=strlen(A);
    int lenB=strlen(B);
    if(lenA != lenB)
        return 0;
    int i = 0;
    int j = lenA-1;
    while(i < j)
        if(A[i] == B[i])
            i += 1;
        else if(A[j] == B[j])
            j -= 1;
        else
            break;
    for(int k=0;k<j-i+1;k++)
        if(A[i+k] != B[j-k])
            return 0;
    i -= 1;
    j += 1;
    int num_ways = 1;
    while(i >= 0 && j < lenB){
        if(A[i] == B[j]){
            num_ways += 1;
            i -= 1;
            j += 1;
        }
        else
            break;
    }
    return num_ways;
}
int main(){
    char*a=getstr();
    char*b=getstr();
    printf("%d\n", solve(a, b));
    return 0;
}
