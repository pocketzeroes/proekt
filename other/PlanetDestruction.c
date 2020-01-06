#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define PI2 6.28318530718
#define EPSILON 1e-8

typedef struct{
    double left, right;
}Virus;

typedef struct{
    double reachTime, angle, speed; 
}Ship;

int cmpfunc(const void *a, const void *b){
    Virus first = *(Virus*) a;
    Virus second = *(Virus*) b;
    double value = first.left - second.left;
    if (value == 0)
        return (first.right - second.right) > (second.right - first.right);
    return (value) > (-value);
}

int check(double currtime, Ship ships[], int numships){
    Virus segments[20005];
    int numsegments = 0;
    for (int i=0; i<numships; i++){
        if (ships[i].reachTime > currtime)
            continue;
        double range = ships[i].speed * (currtime - ships[i].reachTime);
        if (range >= M_PI)
            return 1;
        double left  = ships[i].angle - range;
        double right = ships[i].angle + range;
        Virus curr;
        if (left < 0){
            curr.left = -EPSILON;
            curr.right = right;
            segments[numsegments++] = curr;
            curr.right = PI2 + EPSILON;
            curr.left = PI2 + left;
            segments[numsegments++] = curr;
        }
        else if (right > PI2){
            curr.right = PI2 + EPSILON;
            curr.left = left;
            segments[numsegments++] = curr;
            curr.left = -EPSILON;
            curr.right = right - PI2;
            segments[numsegments++] = curr;
        }
        else {
            curr.left  = left;
            curr.right = right;
            segments[numsegments++] = curr;
        }
    }
    if (numsegments == 0)
        return 0;
    qsort(segments, numsegments, sizeof(Virus), cmpfunc);
    if (segments[0].left > 0)
        return 0;
    double rightedge = segments[0].right;
    for (int i = 0; i<numsegments; i++){
        if (segments[i].right - rightedge > -EPSILON){
            if (rightedge - segments[i].left > -EPSILON)
                rightedge = segments[i].right;
            else
                return 0;
        }
    }
    return (rightedge - PI2 > -EPSILON);
}
void run(){
    int rad, numship;
    scanf("%d %d", &rad, &numship);
    Ship ship[10002];
    for (int i=0; i<numship; i++){
        double x, y, rocketspeed, virusspeed;
        scanf("%lf %lf %lf %lf", &x, &y, &rocketspeed, &virusspeed);
        double distance = sqrt(x*x + y*y) - rad;
        Ship curr;
        curr.reachTime = distance / rocketspeed;
        curr.angle = atan2(y, x) + M_PI;
        curr.speed = virusspeed/rad;
        ship[i] = curr;
    }
    double low  = 0;
    double high = 20000000;
    while (high - low > EPSILON){
        double mid = (low + high)/2;
        if (check(mid, ship, numship))
            high = mid;
        else
            low = mid;
    }
    printf ("%lf\n", low);
}
int main(){
    int test;
    scanf ("%d", &test);
    while (test--)
        run();
    return 0;
}
