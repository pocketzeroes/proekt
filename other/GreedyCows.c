#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define epsilon 0.000000001
typedef struct{
    double x, y;
}pt;
pt newpt(){
   return(pt){1000001.0, 1000001.0};
}
int cmpPt(const void*pa, const void*pb){
    pt*tva=(pt*)pa;
    pt*oth=(pt*)pb;
    if(tva->x == oth->x)
        return(tva->y < oth->y)?-1:1;
    return(tva->x < oth->x)?-1:1;
}
int N, numHull, lo = 0, hi = 100000, best;
ll M, combo [100010][5];
pt start, ori [110], hull [110];

double dist(pt a, pt b){
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}
bool ccw(pt a, pt b, pt c){
    return (b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x) > epsilon;
}
bool collinear(pt a, pt b, pt c){
    return fabs(a.x*b.y+b.x*c.y+c.x*a.y-(a.y*b.x+b.y*c.x+c.y*a.x)) < epsilon;
}
int smallerAngle(const void*pa, const void*pb){
    pt*a=(pt*)pa;
    pt*b=(pt*)pb;
    double anga = atan2(a->y-start.y, a->x-start.x),
           angb = atan2(b->y-start.y, b->x-start.x);
    if(collinear(start, *a, *b) && fabs(angb-anga) < epsilon)
        return dist(start, *a) > dist(start, *b) ? 1: -1;
    return(anga > angb ? 1: -1);
}
int findHull(pt points [110], pt hull [110]){
    int top = 1, n = N;
    if(n <= 3){
        for(int i = 0; i < n; i++){
            hull[i].x = points[i].x;
            hull[i].y = points[i].y;
        }
        hull[n].y = points[0].x;
        hull[n].y = points[0].y;
        return n;
    }
    start.x = points[0].x;
    start.y = points[0].y;
    qsort(points+1, n-1, sizeof(pt), smallerAngle);
    hull[0].x = start.x;
    hull[0].y = start.y;
    hull[1].x = points[1].x;
    hull[1].y = points[1].y;
    points[n].x = start.x;
    points[n].y = start.y;
    for(int i = 2; i <= n; i++){
        while(top >= 1 && !ccw(hull[top-1], hull[top], points[i]))
            top--;
        top++;
        hull[top].x = points[i].x;
        hull[top].y = points[i].y;
    }
    return top;
}
bool checkIt(int x){
    int points1 = x/numHull, count1 = numHull-(x%numHull),
        points2 = points1+1, count2 = x%numHull;
    ll ret = combo[x][4]+combo[x][2]+1;
    ret -= (combo[points1][2]+combo[points1][3]*(ll)(x-points1)+combo[points1][4])*(ll)count1;
    ret -= (combo[points2][2]+combo[points2][3]*(ll)(x-points2)+combo[points2][4])*(ll)count2;
    return ret >= M;
}
int main(){
    memset(combo, 0, sizeof(combo));
    combo[0][0] = 1;
    for(int i=1; i<100010; i++){
        combo[i][0] = 1;
        for(int j=1; j<5; j++)
            combo[i][j] = combo[i-1][j]+combo[i-1][j-1];
    }
    scanf("%lld %d", &M, &N);
    for(int i=0; i<N; i++)
        scanf("%lf %lf", &ori[i].x, &ori[i].y);
    numHull = findHull(ori, hull);
    while(lo <= hi){
        int mid = (lo+hi)/2;
        if(checkIt(mid)){
            best = mid;
            hi = mid-1;
        }
        else
            lo = mid+1;
    }
    printf("%d\n", best);
    return 0;
}
