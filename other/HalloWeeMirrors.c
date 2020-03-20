#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef struct{
    int x1, x2, y1, y2;
}Mirror;

typedef struct{
    int x1, y1, count;
}Person;

int dotProd(int v1x, int v1y, int v2x, int v2y){
    return (v1x * v2x) + (v1y * v2y);
}
int main(){
    int mirrors, standingLocations;
    while(scanf("%d", &mirrors)==1&& mirrors != 0){
        Mirror MirrorLoc[100]; clr(MirrorLoc);
        Person PersonLoc[100]; clr(PersonLoc);
        for(int i=0; i<mirrors; ++i)
            scanf("%d %d %d %d", &MirrorLoc[i].x1, &MirrorLoc[i].y1, &MirrorLoc[i].x2, &MirrorLoc[i].y2);
        scanf("%d", &standingLocations);
        for(int j=0; j<standingLocations; ++j)
            scanf("%d %d", &PersonLoc[j].x1, &PersonLoc[j].y1);
        for(int k=0; k<standingLocations; ++k){
            for(int i=0; i<mirrors; ++i){
                int v1x = MirrorLoc[i].x2 - MirrorLoc[i].x1,
                    v1y = MirrorLoc[i].y2 - MirrorLoc[i].y1,
                    v2x = MirrorLoc[i].x1 - MirrorLoc[i].x2,
                    v2y = MirrorLoc[i].y1 - MirrorLoc[i].y2,
                    p1x = PersonLoc[k].x1 - MirrorLoc[i].x1,
                    p1y = PersonLoc[k].y1 - MirrorLoc[i].y1,
                    p2x = PersonLoc[k].x1 - MirrorLoc[i].x2,
                    p2y = PersonLoc[k].y1 - MirrorLoc[i].y2;
                int prod1 = dotProd(v1x, v1y, p1x, p1y),
                    prod2 = dotProd(v2x, v2y, p2x, p2y);
                if(prod1 >= 0 && prod2 >= 0 )
                    PersonLoc[k].count++;
            }
            printf("%d\n", PersonLoc[k].count);
        }
        puts("");
    }
    return 0;
}
