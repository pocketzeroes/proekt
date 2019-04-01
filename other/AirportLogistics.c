#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
typedef struct{
    double x1, y1, x2, y2;
}Conveyor;

void pointToLine(double px, double py, Conveyor cv, int fw, double*q){
    double dx = cv.x2 - cv.x1;
    double dy = cv.y2 - cv.y1;
    double cvlen = sqrt(dx*dx + dy*dy);
    dx = dx / cvlen;
    dy = dy / cvlen;
    double dd = fabs((cv.x1 - px) * dy - (cv.y1 - py) * dx);
    double dq = (px - cv.x1) * dx + (py - cv.y1) * dy;
    dq += fw * dd / sqrt(3);
    if(dq < 0){
        q[0] = sqrt((cv.x1 - px) * (cv.x1 - px) + (cv.y1 - py) * (cv.y1 - py));
        q[1] = 0;
    }
    else if(dq > cvlen){
        q[0] = sqrt((cv.x2 - px) * (cv.x2 - px) + (cv.y2 - py) * (cv.y2 - py));
        q[1] = cvlen;
    }
    else{
        q[0] = dd * 2.0 / sqrt(3);
        q[1] = dq;
    }
}
double solve(double ax, double ay, double bx, double by, Conveyor*conveyors){
    int k = 2*n + 2;
    double px[k]; memset(px, 0, sizeof(px));
    double py[k]; memset(py, 0, sizeof(py));
    px[0] = ax, py[0] = ay;
    px[1] = bx, py[1] = by;
    for(int i=0; i<n; i++){
        px[2*i+2] = conveyors[i].x1;
        py[2*i+2] = conveyors[i].y1;
        px[2*i+3] = conveyors[i].x2;
        py[2*i+3] = conveyors[i].y2;
    }
    double dist[k][k];
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            double dx = px[j] - px[i];
            double dy = py[j] - py[i];
            dist[i][j] = sqrt(dx*dx + dy*dy);
        }
    }
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            for(int t = 0; t < n; t++){
                double q1[2]={0};
                double q2[2]={0};
                pointToLine(px[i], py[i], conveyors[t],  1, q1);
                pointToLine(px[j], py[j], conveyors[t], -1, q2);
                if (q1[1] < q2[1]){
                    double d = q1[0] + 0.5 * (q2[1] - q1[1]) + q2[0];
                    if (d < dist[i][j])
                        dist[i][j] = d;
                }
            }
        }
    }
    for(int t = 0; t < k; t++){
        for(int i = 0; i < k; i++){
            for(int j = 0; j < k; j++){
                if (dist[i][j] > dist[i][t] + dist[t][j])
                    dist[i][j] = dist[i][t] + dist[t][j];
            }
        }
    }
    return dist[0][1];
}
int main(){
    double ax, ay, bx, by;
    scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
    scanf("%d", &n);
    Conveyor conveyors[n];
    for(int i=0; i<n; i++)
        scanf("%lf %lf %lf %lf", &conveyors[i].x1, &conveyors[i].y1, &conveyors[i].x2, &conveyors[i].y2);
    double ans = solve(ax, ay, bx, by, conveyors);
    printf("%.10lf\n", ans);
    return 0;
}
