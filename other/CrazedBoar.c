#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef double dbl;

typedef struct{
    dbl  theta;
    bool begin;
}Event;
Event newevent(dbl a, bool b){
    return(Event){a,b};
}
int cmpE(const void*pa, const void*pb){
    Event*tva=(Event*)pa;
    Event*oth=(Event*)pb;
    return(tva->theta < oth->theta)?-1:1;
}
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Event*pushbackE(Event*array, int *size, Event value){
  Event*output = resizeArray(array, Event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Event*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////

bool headTree (dbl x, dbl y, dbl r, dbl b, dbl d, dbl*theta1, dbl*theta2){
    dbl px = y;
    dbl py = -x;
    dbl p = sqrt(x*x+y*y);
    dbl dist = (p*p + d*d - (b+r)*(b+r)) / 2.0 / p;
    dbl perpsq = d*d - dist*dist;
    if(perpsq <= 0)
        return false;
    dbl perp = sqrt(perpsq);
    dbl x1 = dist * x / p + perp * px / p;
    dbl y1 = dist * y / p + perp * py / p;
   *theta1 = atan2(y1, x1);
    dbl x2 = dist * x / p - perp * px / p;
    dbl y2 = dist * y / p - perp * py / p;
   *theta2 = atan2(y2, x2);
    return true;
}
bool flankTree(dbl x, dbl y, dbl r, dbl b, dbl d, dbl*theta1, dbl*theta2){
    dbl l = sqrt( x*x + y*y - (r+b)*(r+b) );
    if(l > d)
        return false;
    dbl p = sqrt( x*x + y*y );
    dbl sint = l/p;
    dbl cost = (r+b)/p;
    dbl vx = -x * (r+b) / p;
    dbl vy = -y * (r+b) / p;
    dbl w1x = cost * vx - sint * vy;
    dbl w1y = sint * vx + cost * vy;
   *theta1 = atan2(y + w1y, x + w1x);
    dbl w2x = cost * vx + sint * vy;
    dbl w2y = -sint * vx + cost * vy;
   *theta2 = atan2(y + w2y, x + w2x);
    return true;
}
int main(){
    int n;
    scanf("%d", &n);
    dbl xs[n];
    dbl ys[n];
    dbl rs[n];
    for(int i=0; i<n; i++)
        scanf("%lf %lf %lf", &xs[i], &ys[i], &rs[i]);
    dbl b, d;
    scanf("%lf %lf", &b, &d);

    int treecnt = 0;
    vece events = newVecE();
    for(int i=0; i<n; i++){
        dbl theta1, theta2;
        if(headTree(xs[i], ys[i], rs[i], b, d, &theta1, &theta2) && theta1 != theta2){
            pbe(events, newevent(theta1, true ));
            pbe(events, newevent(theta2, false));
            if(theta2 < theta1)
                treecnt++;
        }
    }
    for(int i=0; i<n; i++){
        dbl theta1, theta2;
        if(flankTree(xs[i], ys[i], rs[i], b, d, &theta1, &theta2) && theta1 != theta2){
            pbe(events, newevent(theta1, true ));
            pbe(events, newevent(theta2, false));
            if(theta2 < theta1)
                treecnt++;
        }
    }
    qsort(events.ptr, events.sz, sizeof(Event), cmpE);
    dbl totlen = 0;
    dbl last = -M_PI;
    for(int z=0;z<events.sz;z++){Event it = events.ptr[z];
        if(treecnt == 0)
            totlen += it.theta - last;
        last = it.theta;
        if(it.begin)
            treecnt++;
        else
            treecnt--;
    }
    if(treecnt == 0)
        totlen += (M_PI - last);
    dbl prob = totlen / (2.0*M_PI);
    printf("%.30lf\n", prob);
    return 0;
}
