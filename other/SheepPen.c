#pragma GCC optimize "-O3"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define MAX 1000
#define PI (3.141592653589793)
#define EPS 0.0000000001
int len[MAX];
int N;
int lastsign;

void centerInside() {
    int i;
    double sum,rad;
    sum = 0;
    rad = len[N-1]/2.0;
    for (i=0; i<N-1; i++) {
        sum += 2*asin(len[i]/2.0/rad);
    }
    if (sum < PI) lastsign = -1;
    else lastsign = 1;
}
double sumAngles(double r) {
       int i;
       double sum,angle;
       sum = 0;
       for (i=0; i<N; i++) {
           angle = 2*asin(len[i]/2.0/r);
           if (i<N-1) sum += angle;
           else {
                sum += lastsign*angle;
           }
       }
       return sum;
}
double sumAreas(double r) {
       int i;
       double h,sum,area;
       sum = 0;
       for (i=0; i<N; i++) {
           h = sqrt(r*r - (len[i]/2.0)*(len[i]/2.0));
           area = h*len[i]/2.0;
           if (i<N-1) sum += area;
           else sum += lastsign*area;
       }
       return sum;
}
int cmpfnc(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}
int main() {
    int k,i,sumlen;
    double radius,left,right,mid,maxarea,area;
        scanf("%d",&N);
        sumlen = 0;
        for (i=0; i<N; i++) {
            scanf("%d",&len[i]);
            sumlen += len[i];
        }
        qsort(len,N,sizeof(int),cmpfnc);
        maxarea = 0;
        for (; N>=3; N--) {
            if (len[N-1] == sumlen-len[N-1]) {
               if (maxarea < 0) maxarea = 0;
            }
            else {
               if (len[N-1] < sumlen-len[N-1]) {
                    centerInside();
                    if (lastsign > 0) {
                        radius = len[N-1]/2.0;
                        while (sumAngles(radius) > 2*PI) {
                              radius *= 2;
                        }
                        left = len[N-1]/2.0;
                        right = radius;
                        while (right-left > EPS) {
                              mid = (left+right)/2;
                              if (sumAngles(mid) > 2*PI) left = mid;
                              else right = mid;
                        }
                    }
                    else {
                        radius = len[N-1]/2.0;
                        while (sumAngles(radius) < 0) {
                              radius *= 2;
                        }
                        left = len[N-1]/2.0;
                        right = radius;
                        while (right-left > EPS) {
                              mid = (left+right)/2;
                              if (sumAngles(mid) < 0) left = mid;
                              else right = mid;
                        }
                    }
                    area = sumAreas(left);
                    if (area > maxarea) maxarea = area;
               }
            }
            sumlen -= len[N-1];
        }
        printf("%.2lf\n",maxarea);
    return 0;
}
