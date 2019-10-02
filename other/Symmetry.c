#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
int gcd( int a, int b ){
    return b==0 ? a : gcd( b, a%b );
}
////////////////////////////////////////////////////////////
typedef struct Point{
    int x, y;
}Point;
Point newPoint(int x, int y){
    return(Point){x,y};
}
int cmpPt(const void*pa, const void*pb){
    Point*t=(Point*)pa;
    Point*p=(Point*)pb;
    int diff = t->x - p->x;
    if(diff==0)
        diff = t->y - p->y;
    return diff;
}
bool binarySearch(Point*arr, int r, Point x){
  r--;
  int l = 0;
  while(l <= r){
    int m = l + (r-l)/2;
    if(cmpPt(&arr[m], &x)==0)
      return true;
    if(cmpPt(&arr[m], &x)< 0)
      l = m + 1;
    else
      r = m - 1;
  }
  return false;
}


typedef struct Line{
    int a, b, c;
}Line;
Line newLine(int a, int b, int c){
    Line this;
    int g = gcd(abs(a), gcd( abs(b), abs(c)));
    a /= g;
    b /= g;
    c /= g;
    if(a<0 || (a==0 && b<0) || (a==0 && b==0 && c<0)){
        a = -a;
        b = -b;
        c = -c;
    }
    this.a = a;
    this.b = b;
    this.c = c;
    return this;
}
int cmpLn(const void*pa, const void*pb){
    Line*t=(Line*)pa;
    Line*l=(Line*)pb;
    int diff = t->a - l->a;
    if( diff==0 )
        diff = t->b - l->b;
    if( diff==0 )
        diff = t->c - l->c;
    return diff;
}

int main(){
    int n = in_nextInt();
    int triangle[n*(n+1)/2+1]; clr(triangle);
    int tri = 0;
    for(int i=1; i<=n; i++){
        tri += i;
        triangle[tri] = i;
    }
    Point spots[n];
    for(int i=0; i<n; i++){
        int x = in_nextInt()*2;
        int y = in_nextInt()*2;
        spots[i] = newPoint(x, y);
    }
    int midpointsSz=n*(n-1)/2;
    Point midpoints[midpointsSz];
    Line  midlines [midpointsSz];
    Line  lines    [midpointsSz];
    int k=0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int x1 = spots[i].x;
            int y1 = spots[i].y;
            int x2 = spots[j].x;
            int y2 = spots[j].y;
            int midx = (x1+x2)/2;
            int midy = (y1+y2)/2;
            midpoints[k] = newPoint( midx, midy );
            int a = x2-x1;
            int b = y2-y1;
            int c = a*midx + b*midy;
            midlines[k] = newLine( a, b, c );
            a = y2-y1;
            b = x1-x2;
            c = a*x1 + b*y1;
            lines[k] = newLine( a, b, c );
            ++k;
        }
    }
    qsort(spots    ,n          , sizeof(Point), cmpPt);
    qsort(midpoints,midpointsSz, sizeof(Point), cmpPt);
    qsort(midlines ,midpointsSz, sizeof(Line) , cmpLn);
    qsort(lines    ,midpointsSz, sizeof(Line) , cmpLn);
    int max = 0;
    if(n<3)
        max = n;
    else{
        int count = 2;
        Point lastpoint = midpoints[0];
        for( int i=1; i<midpointsSz; i++){
            Point thispoint = midpoints[i];
            if(cmpPt(&thispoint, &lastpoint) == 0)
                count += 2;
            else{
                if(binarySearch(spots, n, lastpoint))
                    ++count;
                if( count>max )
                    max=count;
                count = 2;
            }
            lastpoint = thispoint;
        }
        count = 2;
        Line lastline = midlines[0];
        for(int i=1; i<midpointsSz; i++){
            Line thisline = midlines[i];
            if(cmpLn(&thisline, &lastline ) == 0 )
                count += 2;
            else{
                for(int z=0;z<n;z++){Point spot = spots[z];
                    if(lastline.a*spot.x + lastline.b*spot.y == lastline.c)
                        ++count;
                }
                if(count > max)
                   max = count;
                count = 2;
            }
            lastline = thisline;
        }
        count = 1;
        lastline = lines[0];
        for(int i=1; i<midpointsSz; i++){
            Line thisline = lines[i];
            if(cmpLn(&thisline, &lastline ) == 0)
                ++count;
            else{
                count = triangle[count]+1;
                if(count > max)
                   max = count;
                count = 1;
            }
            lastline = thisline;
        }
    }
    printf("%d\n", n - max);
    return 0;
}
