#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX    =  1000};
enum{ MAXD   = 10000};
const double INF = 10. * MAXD * MAXD;

typedef struct{
    double x, y;
}pt;

pt   judges[MAX], tar  [MAX], feather[MAX];
bool usedJ [MAX], usedT[MAX], usedF  [MAX];
int  nJudge, nTar, nFeath;

int main(){
    scanf("%d %d %d", &nJudge, &nTar, &nFeath);
    for(int i=0; i<nJudge; i++){
        scanf("%lf %lf", &judges[i].x, &judges[i].y);
        usedJ[i] = false;
    }
    for(int i=0; i<nTar; i++){
        scanf("%lf %lf", &tar[i].x, &tar[i].y);
        usedT[i] = false;
    }
    for(int i=0; i<nFeath; i++){
        scanf("%lf %lf", &feather[i].x, &feather[i].y);
        usedF[i] = false;
    }
    double total = 0.0;
    for(int i=0; i<nJudge; i++){
        double minDist = INF;
        int savj, savk;
        for(int j=0; j<nJudge; j++){
            if (usedJ[j])
                continue;
            for(int k=0; k<nTar; k++){
                if (usedT[k])
                    continue;
                double xdiff = judges[j].x-tar[k].x;
                double ydiff = judges[j].y-tar[k].y;
                double dist = xdiff*xdiff + ydiff*ydiff;
                if (dist < minDist){
                    minDist = dist;
                    savj = j;
                    savk = k;
                }
            }
        }
        total += sqrt(minDist);
        usedJ[savj] = true;
        usedT[savk] = true;
    }
    for(int i=0; i<nJudge; i++)
        usedJ[i] = false;
    for(int i=0; i<nJudge; i++){
        double minDist = INF;
        int savj, savk;
        for(int j=0; j<nJudge; j++){
            if (usedJ[j])
                continue;
            for(int k=0; k<nFeath; k++){
                if (usedF[k])
                    continue;
                double xdiff = judges[j].x-feather[k].x;
                double ydiff = judges[j].y-feather[k].y;
                double dist = xdiff*xdiff + ydiff*ydiff;
                if (dist < minDist){
                    minDist = dist;
                    savj = j;
                    savk = k;
                }
            }
        }
        total += sqrt(minDist);
        usedJ[savj] = true;
        usedF[savk] = true;
    }
    printf("%.6lf\n", total);
    return 0;
}
