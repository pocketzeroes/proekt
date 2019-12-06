#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#define st first
#define nd second

typedef struct{
    int x, y, z;
}re;
typedef struct{
  re first, second;
}prr;

enum{N =(int)1e3 + 10};
int a, b, c, m;
re chips[N];
prr cubes[N];//prr{re,re}

bool valid(prr cur){
    return cur.st.x <= cur.nd.x && cur.nd.x <= a && cur.st.y <= cur.nd.y && cur.nd.y <= b && cur.st.z <= cur.nd.z && cur.nd.z <= c;
}
bool contain(prr cube, re chip){
    return cube.st.x <= chip.x && chip.x <= cube.nd.x && cube.st.y <= chip.y && chip.y <= cube.nd.y && cube.st.z <= chip.z && chip.z <= cube.nd.z;
}
void solve(){
    for(int i = 1; i <= m; ++i)
        scanf("%d %d %d", &chips[i].x, &chips[i].y, &chips[i].z);
    for(int i = 1; i <= m; ++i)
        scanf("%d %d %d %d %d %d", &cubes[i].st.x, &cubes[i].st.y, &cubes[i].st.z, &cubes[i].nd.x, &cubes[i].nd.y, &cubes[i].nd.z);
    for(int i = 1; i <= m; ++i)
        if(!valid(cubes[i])){
            puts("NO");
            return;
        }
    for(int i = 1; i <= m; ++i)
        if(!contain(cubes[i], chips[i])){
            puts("NO");
            return;
        }
    for(int i = 1; i <= m; ++i)
        for(int j = i + 1; j <= m; ++j){
                prr intersect=(prr){(re){fmax(cubes[i].st.x, cubes[j].st.x), fmax(cubes[i].st.y, cubes[j].st.y), fmax(cubes[i].st.z, cubes[j].st.z)},
                                    (re){fmin(cubes[i].nd.x, cubes[j].nd.x), fmin(cubes[i].nd.y, cubes[j].nd.y), fmin(cubes[i].nd.z, cubes[j].nd.z)}};
                if(valid(intersect)){
                    puts("NO");
                    return;
                }
            }
    ll vol = 0;
    for(int i = 1; i <= m; ++i)
        vol += (ll)(cubes[i].nd.x - cubes[i].st.x + 1) * (cubes[i].nd.y - cubes[i].st.y + 1) * (cubes[i].nd.z - cubes[i].st.z + 1);
    if(vol != (ll)a * b * c)
        puts("NO");
    else
        puts("YES");
}
int main(){
    while(scanf("%d %d %d %d", &a, &b, &c, &m)==4){
        if(a == -1)
            break;
        solve();
        puts("");
    }
    return 0;
}
