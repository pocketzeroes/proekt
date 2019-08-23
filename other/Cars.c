#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

char d[2];
ll x [2], y [2], s[2], w[2], l[2], vx[2], vy[2];
ll sx[2], sy[2], bx, by;
ll t;

void checkTime(ll testTime){
    if (testTime < 0 || testTime > t)
        return;
    ll curx[2], cury[2];
    for(int i = (0); i < 2; ++i){
        curx[i] = x[i] + vx[i]*testTime;
        cury[i] = y[i] + vy[i]*testTime;
    }
    ll dx = llabs(curx[0] - curx[1]);
    ll dy = llabs(cury[0] - cury[1]);
    if (2*dx >= sx[0]+sx[1])
        return;
    if (2*dy >= sy[0]+sy[1])
        return;
    puts("crash");
    exit(0);
}
int main(){
    scanf("%lld", &t);
    getchar();
    for(int i = 0; i < 2; i++){
        d[i]=getchar();
        getchar();
        scanf("%lld %lld %lld %lld %lld", &x[i], &y[i], &s[i], &w[i], &l[i]);
        getchar();
    }
    ll mul = 2 * s[0] * s[1];
    t *= mul;
    for(int i = (0); i < 2; ++i){
        x[i] *= mul;
        y[i] *= mul;
        w[i] *= mul;
        l[i] *= mul;
        if (d[i] == 'N'){
            vx[i] = 0;
            vy[i] = s[i];
            sx[i] = w[i];
            sy[i] = l[i];
        }
        if (d[i] == 'S') {
            vx[i] = 0;
            vy[i] = -s[i];
            sx[i] = w[i];
            sy[i] = l[i];
        }
        if (d[i] == 'E') {
            vx[i] = s[i];
            vy[i] = 0;
            sx[i] = l[i];
            sy[i] = w[i];
        }
        if (d[i] == 'W') {
            vx[i] = -s[i];
            vy[i] = 0;
            sx[i] = l[i];
            sy[i] = w[i];
        }
    }
    bx = (sx[0] + sx[1])/2;
    by = (sy[0] + sy[1])/2;
    checkTime(0);
    checkTime(t);
    for (int factor = -1; factor <= 1; factor += 2) {
        ll dv = vx[0] - vx[1];
        if (dv == 0)
            continue;
        ll testTime = (x[1] - x[0] + factor*bx) / dv;
        checkTime(testTime-1);
        checkTime(testTime);
        checkTime(testTime+1);
    }
    for (int factor = -1; factor <= 1; factor += 2) {
        ll dv = vy[0] - vy[1];
        if (dv == 0)
            continue;
        ll testTime = (y[1] - y[0] + factor*by) / dv;
        checkTime(testTime-1);
        checkTime(testTime);
        checkTime(testTime+1);
    }
    puts("safe");
    return 0;
}
