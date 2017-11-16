#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int TERNARY_ITERATIONS = 50;
enum{ MAXN = 1024};
double x[MAXN][2];
double X1[2], X2[2];
double X[2];
double x_se[2][2];
double x_edges[4][2][2];
double dist_se[2][MAXN];
int N;
double v_walk, v_under;


double directDist(double *p1, double* p2){
    return sqrt( pow( p1[0] - p2[0], 2 ) + pow( p1[1] - p2[1], 2) );
}
double walkOn2edges_evaluate(int segId1, double f1, int segId2, double f2){
    double x_station[2][2];
    for (int d = (0); d < (2); d++){
        x_station[0][d] = x_edges[segId1][0][d] + (x_edges[segId1][1][d] - x_edges[segId1][0][d]) * f1;
        x_station[1][d] = x_edges[segId2][0][d] + (x_edges[segId2][1][d] - x_edges[segId2][0][d]) * f2;
    }
    return directDist(x_se[0], x_station[0]) / v_walk
            + directDist(x_station[0], x_station[1]) / v_under
            + directDist(x_station[1], x_se[1]) / v_walk;
}
double walkOn2edges_ternarysearch2(int segId1, double f1, int segId2){
    double lo = 0.0, hi = 1.0;
    for (int iterations = (0); iterations < (TERNARY_ITERATIONS); iterations++){
        double mid1 = lo + (hi - lo) * 0.4;
        double mid2 = lo + (hi - lo) * 0.6;
        double val1 = walkOn2edges_evaluate(segId1, f1, segId2, mid1);
        double val2 = walkOn2edges_evaluate(segId1, f1, segId2, mid2);
        if(val1 < val2) hi = mid2;
        else lo = mid1;
    }
    return walkOn2edges_evaluate(segId1, f1, segId2, (lo + hi) * 0.5);
}
double walkOn2edges_ternarysearch1(int segId1, int segId2){
    double lo = 0.0, hi = 1.0;
    for (int iterations = (0); iterations < (TERNARY_ITERATIONS); iterations++){
        double mid1 = lo + (hi - lo) * 0.4;
        double mid2 = lo + (hi - lo) * 0.6;
        double val1 = walkOn2edges_ternarysearch2(segId1, mid1, segId2);
        double val2 = walkOn2edges_ternarysearch2(segId1, mid2, segId2);
        if(val1 < val2) hi = mid2;
        else lo = mid1;
    }
    return walkOn2edges_ternarysearch2(segId1, (lo + hi) * 0.5, segId2);
}
double walkOn2edges(){
    double res = 1e100;
    for (int i = (0); i < (4); i++)for (int j = (0); j < (4); j++){
        res = min(res, walkOn2edges_ternarysearch1(i, j));
    }
    return res;
}
double distToStation_evaluate(double *p, double* s, int segId, double f){
    double position[2];
    for (int d = (0); d < (2); d++){
        position[d] = x_edges[segId][0][d] + (x_edges[segId][1][d] - x_edges[segId][0][d]) * f;
    }
    return directDist(p, position) / v_walk + directDist(position, s) / v_under;
}
double distToStation_ternarysearch(double *p, double* s, int segId){
    double lo = 0.0, hi = 1.0;
    for (int iterations = (0); iterations < (TERNARY_ITERATIONS); iterations++){
        double mid1 = lo + (hi - lo) * 0.4;
        double mid2 = lo + (hi - lo) * 0.6;
        double val1 = distToStation_evaluate(p, s, segId, mid1);
        double val2 = distToStation_evaluate(p, s, segId, mid2);
        if(val1 < val2) hi = mid2;
        else lo = mid1;
    }
    return distToStation_evaluate(p, s, segId, (lo + hi) * 0.5);
}
double distToStation(double *p, double *s){
    double res = directDist(p, s) / v_walk;
    for (int i = (0); i < (4); i++){
        res = min(res, distToStation_ternarysearch( p, s, i));
    }
    return res;
}
int main(){
    scanf("%lf %lf", &v_walk, &v_under);
    {
        scanf("%lf %lf %lf %lf", &X1[0], &X1[1], &X2[0], &X2[1]);
        for (int d = (0); d < (2); d++){
            X[d] = X2[d] - X1[d];
        }
        for (int i = (0); i < (2); i++){
            for (int d = (0); d < (2); d++){
                scanf("%lf", &x_se[i][d]);
                x_se[i][d] -= X1[d];
            }
        }
    }
    scanf("%d", &N);
    for (int i = (0); i < (N); i++)for (int d = (0); d < (2); d++){
        scanf("%lf", &x[i][d]);
        x[i][d] -= X1[d];
    }
    for (int i = (0); i < (4); i++){
        x_edges[i][0][0] = ((i&2)?0.0:X[0]);
        x_edges[i][0][1] = ((i&2)?0.0:X[1]);
        x_edges[i][1][0] = ((i&1)?0.0:X[0]);
        x_edges[i][1][1] = ((i&1)?X[1]:0.0);
    }
    double res = directDist(x_se[0], x_se[1]) / v_walk;
    res = min(res, walkOn2edges());
    for (int i = (0); i < (2); i++)for (int n = (0); n < (N); n++){
        dist_se[i][n] = distToStation(x_se[i], x[n]);
    }
    for (int n = (0); n < (N); n++)
        res = min(res, dist_se[0][n] + dist_se[1][n]);
    for (int n1 = (0); n1 < (N); n1++)
        for (int n2 = (0); n2 < (N); n2++){
            res = min(res, dist_se[0][n1] + directDist(x[n1], x[n2]) / v_under + dist_se[1][n2]);
        }
    printf("%.9lf\n", res);
    return 0;
}






















































