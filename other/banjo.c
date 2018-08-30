#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

int    radius;
int    walklen;
double angleOneT;

int inp_nextInt(){
    int x;
    scanf("%d", &x);
    return x;
}
typedef struct{
    double x;
    double y;
}pt;

pt newPt(double myx, double myy){
    pt rez;
    rez.x = myx;
    rez.y = myy;
    return rez;
}
pt translatePt(pt p, double dx, double dy){
    return newPt(p.x + dx, p.y + dy);
}
pt rotatePt(pt p, double angle){
    return newPt(p.x*cos(angle) - p.y*sin(angle), p.x*sin(angle) + p.y*cos(angle));
}
double getAngle(pt p, pt end){
    return atan2(end.y-p.y, end.x-p.x);
}
pt horizFlip(pt p){
    return newPt(p.x, -p.y);
}
double dist(pt p, pt other){
    return sqrt(pow(p.x-other.x,2) + pow(p.y-other.y,2));
}


typedef struct{
    pt start;
    pt end;
    pt center;
}banjo;


banjo newBanjo(pt a, pt b, pt c){
    banjo rez;
    rez.start  = a;
    rez.end    = b;
    rez.center = c;
    return rez;
}
banjo translate(banjo*b, double dx, double dy){
    return newBanjo(translatePt(b->start , dx, dy), 
                    translatePt(b->end   , dx, dy),
                    translatePt(b->center, dx, dy));
}
banjo rotate(banjo*b, double angle){
    return newBanjo(rotatePt(b->start , angle), 
                    rotatePt(b->end   , angle),
                    rotatePt(b->center, angle));
}
bool canGoStraight(banjo*b){
    double disc = radius*radius - b->center.y*b->center.y;
    if(disc <= 0)
        return true;
    double minX = b->center.x - sqrt(disc);
    double maxX = b->center.x + sqrt(disc);
    if(maxX <= 0 || minX >= b->end.x)
        return true;
    return 2*sqrt(disc) <= walklen;
}
void flipHorizEnd(banjo*b){
    b->end = horizFlip(b->end);
}
bool endYIsNeg(banjo*b){
    return b->end.y < 0;
}
double*getbinSearchBounds(banjo*bnj){
    double*ans         = calloc(4, sizeof(double));
    double angleUp     = asin(radius / dist(bnj->start, bnj->center));
    double a           = 1 + pow(tan(angleUp), 2);
    double b           = -2 * bnj->center.x;
    double x           = -b/(2*a);
    double y           = sqrt(radius*radius-pow(bnj->center.x-x,2));
    ans[0]             = atan2(y,x - bnj->center.x);
    angleUp            = atan2(bnj->end.y, bnj->end.x);
    a                  = 1 + pow(tan(angleUp), 2);
    b                  = -2* bnj->center.x;
    double c           = bnj->center.x*bnj->center.x - radius*radius;
    x                  = (-b-sqrt(b*b-4*a*c))/(2*a);
    y                  = sqrt(radius*radius-pow(bnj->center.x-x,2));
    ans[1]             = atan2(y,x- bnj->center.x);
    x                  = (-b+sqrt(b*b-4*a*c))/(2*a);
    y                  = sqrt(radius*radius-pow(bnj->center.x-x,2));
    ans[2]             = atan2(y,x- bnj->center.x);
    double centerToEnd = getAngle(bnj->center, bnj->end);
    double theta       = acos(radius/(dist(bnj->center, bnj->end)));
    ans[3]             = centerToEnd + theta;
    return ans;
}
double getChordLength(double angle){
    return radius*sqrt(2*(1-cos(angle)));
}
pt ptOnCircleAtAngle(banjo*b, double angle){
    return newPt(b->center.x + radius * cos(angle), b->center.y + radius * sin(angle));
}
void setAngleOneT(){
    angleOneT = acos(1-1.0 * walklen * walklen / (2 * radius * radius));
}
    
enum{ SIZE = 8};

double solveInstance(banjo*problem, double left, double right){
    pt leftPt  = ptOnCircleAtAngle(problem, left );
    pt rightPt = ptOnCircleAtAngle(problem, right);
    double ans = dist(problem->start, leftPt )+
                 dist(problem->end  , rightPt);
    if(walklen == 0)
        return ans + radius*(left-right);
    double fullAngle = left-right;
    int    fullWalks = (int)(fullAngle/angleOneT);
    ans += walklen*fullWalks;
    double leftOverAngle = fullAngle - fullWalks*angleOneT;
    ans += getChordLength(leftOverAngle);
    return ans;
}
double solveBest(banjo*problem, double leftAngle, double low, double high){
    double best = 100000;
    for (int loop=0; loop<40; loop++) {
        double mid   = (low+high)/2;
        double delta = min((high-low)/100,1e-5);
        double tmp   = solveInstance(problem, leftAngle, mid);
        double left  = solveInstance(problem, leftAngle, mid-delta);
        double right = solveInstance(problem, leftAngle, mid+delta);
        if (tmp < best) 
            best = tmp;
        if (left < tmp || right > tmp) 
            high = mid;
        else 
            low  = mid;
    }
    return best;
}
double solve(banjo*problem, double*searchBounds){
    if(walklen == 0)
        return solveInstance(problem, searchBounds[0], searchBounds[3]);
    double low  = searchBounds[0];
    double high = searchBounds[1];
    double best = 100000;
    for(int loop=0; loop<40; loop++){
        double mid   = (low+high)/2;
        double delta = min((high-low)/100,1e-5);
        double tmp   = solveBest(problem, mid      , searchBounds[2], searchBounds[3]);
        double left  = solveBest(problem, mid-delta, searchBounds[2], searchBounds[3]);
        double right = solveBest(problem, mid+delta, searchBounds[2], searchBounds[3]);
        if (tmp < best) 
            best = tmp;
        if (left < tmp || right > tmp) 
            high = mid;
        else
            low  = mid;
    }
    return best;
}


int main(){
    int buffer[SIZE];
    for(int i=0; i<SIZE; i++)
        buffer[i] = inp_nextInt();
    while(buffer[6] != 0){
        pt start  = newPt(buffer[0], buffer[1]);
        pt end    = newPt(buffer[2], buffer[3]);
        pt center = newPt(buffer[4], buffer[5]);
        radius    = buffer[6];
        walklen   = buffer[7];
        banjo original  = newBanjo(start, end, center);
        banjo temp      = translate(&original, -start.x, -start.y);
        banjo checkEasy = rotate(&temp, -getAngle(start, end));
        if(canGoStraight(&checkEasy))
            printf("%.2f\n", dist(start, end));
        else{
            banjo translated = translate(&original, -start.x, -start.y);
            banjo problem    = rotate(&translated, -getAngle(start, center));
            if(endYIsNeg(&problem)) 
               flipHorizEnd(&problem);
            setAngleOneT();
            double*binSearchBounds = getbinSearchBounds(&problem);
            printf("%.2f\n", solve(&problem, binSearchBounds));
        }
        for(int i=0; i<SIZE; i++)
            buffer[i] = inp_nextInt();
    }
    return 0;
}
