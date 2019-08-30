#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
    double x, y;
}pt;
pt newpt(double x, double y){
    return(pt){x,y};
}
pt opAdd(pt t, pt ano){
    return newpt(t.x + ano.x, t.y + ano.y);
}
pt opSub(pt t, pt ano){
    return newpt(t.x - ano.x, t.y - ano.y);
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        double M, B, D, T;
        scanf("%lf%lf%lf%lf", &M, &B, &D, &T);
        double sx = B*T;
        double t = 11 / M;
        pt c1 = newpt(sx, -0.5);
        pt c2 = newpt(sx + B*t, 10.5);
        pt v = opSub(c2, c1);
        pt n = newpt(-v.y, v.x);
        double len = sqrt(n.x*n.x + n.y*n.y);
        n.x /= len;
        n.y /= len;
        n.x *= 0.5;
        n.y *= 0.5;
        pt n2 = newpt(-n.x, -n.y);
        pt d1 = opAdd(c1, n );
        pt d2 = opAdd(c2, n );
        pt d3 = opAdd(c1, n2);
        pt d4 = opAdd(c2, n2);
        bool never = 1;
        for(int i=0; i<10; i++){
            pt a, b;
            bool ok = 1;
            double sl = D + i * 4, sr = sl + 2;
            double p;
            p = (d2.y - 5) / (d2.y - d1.y);
            double xl = p * d1.x + (1 - p) * d2.x;
            p = (d4.y - 5) / (d4.y - d3.y);
            double xr = p * d3.x + (1 - p) * d4.x;
            if (sl <= xr && sr >= xl) {
                printf("Collision with bicycle %d\n", i + 1);
                never = 0;
                break;
            }
            if (xr < sl) {
                if (i == 0)
                    puts("Max beats the first bicycle");
                else
                    printf("Max crosses safely after bicycle %d\n", i);
                never = 0;
                break;
            }
        }
        if (never)
            puts("Max crosses safely after bicycle 10");
    }
    return 0;
}
