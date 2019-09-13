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

struct Plot;
typedef struct{
    double      value;
    bool        lo;
    struct Plot*plot;
    int         index;
}Coordinate;
typedef struct Plot{
    Coordinate*xlo;
    Coordinate*xhi;
    Coordinate*ylo;
    Coordinate*yhi;
}Plot;

Coordinate*newCoordinate(double value, bool lo, Plot*plot){
    Coordinate*rv=calloc(1, sizeof(Coordinate));
    rv->value = value;
    rv->lo    = lo;
    rv->plot  = plot;
    rv->index = -1;
    return rv;
}
int cmpC(const void*pa, const void*pb){
    Coordinate**pt=(Coordinate**)pa;
    Coordinate**pc=(Coordinate**)pb;
    Coordinate*t = *pt;
    Coordinate*c = *pc;
    return(t->value < c->value)?-1:1;
}

int main(){
    int n = in_nextInt();
    Coordinate*xs[n+n]; clr(xs);
    Coordinate*ys[n+n]; clr(ys);
    for(int i=0; i<n; i++){
        int index = i+i;
        Plot*p = calloc(1, sizeof(Plot));
        double d1,d2,d3,d4;
        scanf("%lf%lf%lf%lf", &d1, &d2, &d3, &d4);
        xs[index  ] = newCoordinate(d1, true , p);
        ys[index  ] = newCoordinate(d2, true , p);
        xs[index+1] = newCoordinate(d3, false, p);
        ys[index+1] = newCoordinate(d4, false, p);
        p->xlo      = xs[index  ];
        p->ylo      = ys[index  ];
        p->xhi      = xs[index+1];
        p->yhi      = ys[index+1];
    }
    qsort(xs, n+n, sizeof(Coordinate*), cmpC);
    qsort(ys, n+n, sizeof(Coordinate*), cmpC);
    double lasty = ys[0]->value;
    double heights[n+n]; clr(heights);
    for(int i=0; i<n+n; i++){
        ys[i]->index = i;
        if(i>0)
            heights[i-1] = ys[i]->value - lasty;
        lasty = ys[i]->value;
    }
    int counts[n+n]; clr(counts);
    double totalheight = 0.0;
    double area        = 0.0;
    double lastx       = 0.0;
    for(int i=0; i<n+n; i++){
        double thisx = xs[i]->value;
        area += (thisx-lastx)*totalheight;
        Plot*p = xs[i]->plot;
        if( xs[i]->lo ){
            for( int j=p->ylo->index; j<p->yhi->index; j++ ){
                if( counts[j]==0 )
                    totalheight += heights[j];
                ++counts[j];
            }
        }
        else{
            for( int j=p->ylo->index; j<p->yhi->index; j++ ){
                --counts[j];
                if( counts[j]==0 ) 
                    totalheight -= heights[j];
            }
        }
        lastx = thisx;
    }
    printf("%.2f\n", area);
    return 0;
}
