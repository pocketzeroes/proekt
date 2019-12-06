#pragma GCC optimize "-O3" // https://open.kattis.com/problems/treasurespotting
#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;

enum{ Colinear = -1, NoIntersect = 0, Intersect = 1};
enum{ CW = 2, CCW = 3};
enum{ Inside = 4, Outside = 5, OnEdge = 6};
ld fEps = 0.0000000001;

typedef struct{
    ld x, y;
}pt;
pt newpt(ld x, ld y){
    return(pt){x,y};
}
int cmpPt(pt tva, pt oth){
    return(tva.x<oth.x?true:(tva.x==oth.x&&tva.y<oth.y))?-1:1;
}
pt maxp(pt a, pt b){return cmpPt(a,b)>0?a:b;}
pt minp(pt a, pt b){return cmpPt(a,b)<0?a:b;}
bool opEq(pt tva, pt oth){
    return fabsl(oth.x-tva.x) < fEps && fabsl(oth.y - tva.y) < fEps;
}
pt opadd(pt tva, pt oth){
    return newpt(tva.x + oth.x, tva.y + oth.y);
}
pt opsub(pt tva, pt oth){
    return newpt(tva.x - oth.x, tva.y - oth.y);
}
pt opmul(pt tva, ld oth){
    return newpt(tva.x * oth, tva.y * oth);
}
pt opdiv(pt tva, ld oth){
    return newpt(tva.x / oth, tva.y / oth);
}

typedef struct{
    pt p1, p2;
}segment;
typedef struct{
    pt pos, far;
}pirate;
bool peq(pirate p1, pirate p2){
    return opEq(p1.pos, p2.pos);
}


ld dot(pt a, pt b, pt c){
    pt AB = opsub(b, a);
    pt BC = opsub(c, b);
    return AB.x*BC.x+AB.y*BC.y;
}
ld cross(pt A, pt B, pt C){
    pt AB = opsub(B, A),
       AC = opsub(C, A);
    return(AB.x * AC.y - AB.y * AC.x);
}
int orientation(pt p, pt q, pt r){
    ld val = cross(p, q, r);
    if(fabsl(val) < fEps)
        return Colinear;
    return(val > 0) ? CW : CCW;
}
bool onSegment(pt p, segment s){
    bool x = (fabsl(s.p1.x - s.p2.x) < fEps && fabsl(p.x - s.p2.x) < fEps) || (p.x <= fmaxl(s.p1.x, s.p2.x) && p.x >= fminl(s.p1.x, s.p2.x));
    bool y = (fabsl(s.p1.y - s.p2.y) < fEps && fabsl(p.y - s.p2.y) < fEps) || (p.y <= fmaxl(s.p1.y, s.p2.y) && p.y >= fminl(s.p1.y, s.p2.y));
    return x && y;
}
bool intersect(segment s1, segment s2){
    pt a = s1.p1,
       b = s1.p2,
       c = s2.p1,
       d = s2.p2;
    if(orientation(a, b, c) == Colinear && orientation(a, b, d) == Colinear &&
       orientation(c, d, a) == Colinear && orientation(c, d, b) == Colinear){
        pt min_s1 = minp(a, b), max_s1 = maxp(a, b);
        pt min_s2 = minp(c, d), max_s2 = maxp(c, d);
        if(cmpPt(max_s1, min_s2)<0||
           cmpPt(max_s2, min_s1)<0)
            return false;
        pt start = maxp(min_s1, min_s2),
           end   = minp(max_s1, max_s2);
        if(opEq(start, end))
            return true;
        else
            return true;
    }
    ld a1 = b.y - a.y,
       a2 = d.y - c.y;
    ld b1 = a.x - b.x,
       b2 = c.x - d.x;
    ld c1 = a1*a.x + b1*a.y,
       c2 = a2*c.x + b2*c.y;
    ld det = a1*b2 - a2*b1;
    if(fabsl(det) > fEps){
        pt inter = newpt((b2*c1 - b1*c2)/det, (a1*c2 - a2*c1)/det);
        if(onSegment(inter, s1) &&
           onSegment(inter, s2))
            return true;
    }
    return false;
}
ld distsqr(pt p1, pt p2){
    return powl(p1.x-p2.x,2) + powl(p1.y - p2.y, 2);
}
ld sqmag(pt p1){
    return p1.x*p1.x + p1.y*p1.y;
}
ld mag(pt p1){
    return sqrtl(sqmag(p1));
}
ld sproject(pt a, pt b){
    return dot(a, newpt(0, 0), b)/mag(b);
}
pt vproject(pt a, pt b){
    return opdiv(opmul(b, sproject(a, b)), mag(b));
}
bool straddle(segment s1, segment s2){
    ld cross1 = cross(s1.p1, s1.p2, s2.p1);
    ld cross2 = cross(s1.p1, s1.p2, s2.p2);
    if((cross1 > 0 && cross2 > 0) || (cross1 < 0 && cross2 < 0))
        return false;
    if(fabsl(cross1) < fEps && fabsl(cross2) < fEps && orientation(s1.p2, s2.p1, s2.p2) != Colinear)
       return false;
    return true;
}
bool infront(pt pos, pt far, pt treasure){
    pt newfar      = opsub(far     , pos);
    pt newtreasure = opsub(treasure, pos);
    double proj = newfar.x * newtreasure.x+
                  newfar.y * newtreasure.y;
    return proj>0-fEps;
}
int main(){
    int w, p;
    scanf("%d %d", &w, &p);
    ld tx, ty;
    scanf("%Lf %Lf", &tx, &ty);
    segment*walls = calloc(w, sizeof(segment));
    for(int z=0;z<w;z++)
        scanf("%Lf %Lf %Lf %Lf", &walls[z].p1.x, &walls[z].p1.y, &walls[z].p2.x, &walls[z].p2.y);
    pirate*pirates = calloc(p, sizeof(pirate));
    for(int z=0;z<p;z++)
        scanf("%Lf %Lf %Lf %Lf", &pirates[z].pos.x, &pirates[z].pos.y, &pirates[z].far.x, &pirates[z].far.y);
    for(int z=0;z<p;z++){pirate i = pirates[z];
        bool canSee = true;
        if(distsqr(i.pos, (pt){tx,ty}) > distsqr(i.pos,i.far))
            canSee = false;
        if(!infront(i.pos, i.far, (pt){tx,ty}))
            canSee = false;
        for(int _=0;_<p;_++){pirate j = pirates[_];
            if(peq(j, i))
                continue;
            if(!canSee)
                break;
            bool pts = intersect((segment){i.pos,(pt){tx,ty}}, (segment){j.pos, j.pos});
            if(pts)
                canSee = false;
        }
        for(int q=0;q<w;q++){segment j = walls[q];
            if(!canSee)
                break;
            bool pts = intersect((segment){i.pos,(pt){tx,ty}}, j);
            if(pts)
                canSee = false;
        }
        if(canSee)
            puts("visible");
        else
            puts("not visible");
    }
    free(walls);
    free(pirates);
    return 0;
}
