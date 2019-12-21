#include<stdio.h>
#include<math.h>
#define EPS 0.0000001

char buf[100000];
char cmd[1100];
char dist[1100][100];

double X, Y;
double HD;

void FD(int d){
    X += d*cos(HD/180*M_PI);
    Y += d*sin(HD/180*M_PI);
}
void LT(int d) {
    HD+=d;
}
void HOME() {
    HD = 0;
    X = 0;
    Y = 0;
}
int myatoi(char* st, int other) {
    if(st[0] == '?')
        return other;
    return atoi(st);
}
int main(){
    int CASES;
    scanf("%d ", &CASES);
    while(CASES--){
        int cnt;
        int i;
        int turn = 0;
        int n;
        scanf("%d", &n);
        for(i=0;i<n;i++){
            scanf("%s %s", &buf, dist+i);
            cmd[i] = buf[0];
        }
        for(i=0; i<n; i++){
            if(dist[i][0] != '?') 
                continue;
            if(cmd[i] == 'l') 
                turn = 1;
            if(cmd[i] == 'r') 
                turn = 1;
        }
        if(turn) {
            int ang;
            for(ang = 0; ang < 360; ang++){
                HOME();
                for(i=0; i<n; i++){
                    switch(cmd[i]) {
                        case 'f': FD(atoi(dist[i])); break;
                        case 'b': FD(-atoi(dist[i])); break;
                        case 'l': LT(myatoi(dist[i],ang)); break;
                        case 'r': LT(-myatoi(dist[i],ang)); break;
                    }
                }
                if(fabs(X)+fabs(Y) < EPS){
                    printf("%d\n", ang);
                    goto next;
                }
            }
            puts("no angle worked");
        }
        else {
            HOME();
            for(i=0; i<n; i++){
                switch(cmd[i]) {
                    case 'f': FD(myatoi(dist[i],0)); break;
                    case 'b': FD(-myatoi(dist[i],0)); break;
                    case 'l': LT(atoi(dist[i])); break;
                    case 'r': LT(-atoi(dist[i])); break;
                }
            }
            printf("%.0lf\n", sqrt(X*X+Y*Y));
        }
  next:;
    }
    return 0;
}
