#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
double in_nextDouble(){
  double xx;
  scanf("%lf", &xx);
  return xx;
}
double**newmat(int x, int y){
  double**rv = calloc(x, sizeof(double*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(double));
  return rv;
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define back(vv) vv.ptr[vv.sz-1]
/////////////////////////////////////////////
int n;
double theta;
double**image;
double cc[4];
int leftmost = -1;
double eps = 1e-8;



void getColourCount(){
    bool hasSeenColour = false;
    double anglePerPixel = theta / n;
    int colouredPixels = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++)
            cc[j] += image[i][j] * anglePerPixel;
        double sum = image[i][0] + image[i][1] + image[i][2];
        if (!hasSeenColour)
            cc[3] += (1 - sum) * anglePerPixel;
        if (sum > 0){
            hasSeenColour = true;
            colouredPixels++;
        }
    }
}
int*getFullyVisible(){
    vec order = newVec();
    for(int i = 0; i < n; i++){
        int sumc = 0;
        if(image[i][0] > 0)
            sumc++;
        if(image[i][1] > 0)
            sumc++;
        if(image[i][2] > 0)
            sumc++;
        if(sumc == 0)
            continue;
        int c1 = 0;
        for(; c1 < 3; c1++)
            if(image[i][c1] > 0)
                break;
        int c2 = c1 + 1;
        for(; c1 < 3; c1++)
            if(image[i][c1] > 0)
                break;
        if(sumc == 3){
            if (c1 == back(order))
                c1 = 3 - c2 - back(order);
            if (c2 == back(order))
                c2 = 3 - c1 - back(order);
            sumc--;
        }
        if(sumc == 1)
            if(order.sz == 0 || back(order) != c1)
                pb(order, c1);
        if(sumc == 2){
            if (order.sz > 0) {
                if (back(order) == c1) {
                    pb(order, c2);
                    continue;
                }
                if (back(order) == c2) {
                    pb(order, c1);
                    continue;
                }
            }
            if ((c1 + 1) % 3 == c2) {
                pb(order, c1);
                pb(order, c2);
            }
            else{
                pb(order, c2);
                pb(order, c1);
            }
        }
    }
    leftmost = order.ptr[0];
    if(order.sz == 2)
        return order.ptr;
    if(cc[order.ptr[0]] > cc[order.ptr[2]])
        return order.ptr;
    else
        return order.ptr+1;
}
double*rotate(double*p, int count){
    double angle = 0;
    if (count % 3 == 1)
        angle = 2 * M_PI / 3;
    if (count % 3 == 2)
        angle = -2 * M_PI / 3;
    double*rv = calloc(2, sizeof(double));
    rv[0]=cos(angle) * p[0] - sin(angle) * p[1];
    rv[1]=sin(angle) * p[0] + cos(angle) * p[1];
    return rv;
}
double*getBlueMiddle(double angle, bool bottom){
    double*rv = calloc(2, sizeof(double));
    rv[0]=-0.5;
    rv[1]=1./2./tan(angle)*(bottom?-1:1);
    return rv;
}
double*intersectCircles(double*m1, double*m2){
    double a = m1[0], 
           b = m1[1], 
           c = m2[0],
           d = m2[1];
    double divisor = (a - c) * (a - c) + (b - d) * (b - d);
    if(divisor < eps){
        double*rv = calloc(2, sizeof(double));
        rv[0]=2*m1[0];
        rv[1]=2*m1[1];
        return rv;
    }
    double numerator = 2 * (b * c - a * d);
    double*rv = calloc(2, sizeof(double));
    rv[0]= (b-d)*numerator/divisor;
    rv[1]=-(a-c)*numerator/divisor;
    return rv;
}
double getDirectionAngle(double blackLeader, double*pos){
    double endpo[2] = {-1, 0};
    double*endpoint = rotate(endpo, leftmost + 1);
    double leftAngle = atan2(endpoint[1] - pos[1], endpoint[0] - pos[0]);
    double beginAngle = leftAngle + blackLeader;
    double alpha = beginAngle - theta / 2;
    if( alpha > M_PI)
        alpha -= 2 * M_PI;
    if( alpha < -M_PI)
        alpha += 2 * M_PI;
    return alpha;
}

int main(){
    n = in_nextInt();
    theta = in_nextDouble();
    image = newmat(n, 3);//of double
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 3; j++)
            image[i][j] = in_nextDouble();
    getColourCount();
    int*fullyVisible = getFullyVisible();
    double*m1 = rotate(getBlueMiddle(cc[fullyVisible[0]], true), fullyVisible[0] + 1);
    double*m2 = rotate(getBlueMiddle(cc[fullyVisible[1]], false), fullyVisible[1] + 1);
    double*ans = intersectCircles(m1, m2);
    double angle = getDirectionAngle(cc[3], ans);
    printf("%lf", ans[0]);
    printf(" ");
    printf("%lf", ans[1]);
    printf(" ");
    printf("%lf\n", angle);
    return 0;
}
