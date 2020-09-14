#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int a[10],b[10];
int u[10][10],v[10][10],d[10];

bool isTransformable(char*s, char*t){
    clr(a);
    clr(b);
    int n=strlen(s),i,j;
    for(i=0; i<n; i++){
       a[s[i]^'0']++;
       b[t[i]^'0']++;
    }
    for(i=0; i<10; i++)
        if(a[i] != b[i])
            return 0;
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(d, 0, sizeof(d));
    for(i=0; i<n; i++){
        for(j=(s[i]^'0')+1; j<10; j++)
            u[j][s[i]^'0'] += d[j];
        d[s[i]^'0']++;
    }
    memset(d, 0, sizeof(d));
    for(i=0; i<n; i++){
        for(j=(t[i]^'0')+1; j<10; j++)
            v[j][t[i]^'0'] += d[j];
        d[t[i]^'0']++;
    }
    for(i=0; i<10; i++)
        for(j=0; j<10; j++)
            if(u[i][j] < v[i][j])
                return 0;
    return 1;
}
