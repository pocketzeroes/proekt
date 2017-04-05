#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

int main() {
    int n;
    scanf("%d", &n);
    int maxX = 0, maxY = 0;
    pair points[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i].first , &points[i].second);
        maxX = max(maxX, points[i].first);
        maxY = max(maxY, points[i].second);
    }
    int index = -1;
    for (int i = 0; i < n; i += 1) {
        pair myp = newPair(maxX, maxY);
        if( points[i].first  == myp.first&&
            points[i].second == myp.second  )
        {
            index = i + 1;
        }
    }
    printf("%d", index);
    return 0;
}

