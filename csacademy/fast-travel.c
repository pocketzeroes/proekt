#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

enum{ kMaxN = 1001};
struct Point {
    bool special;
    int x, y;
} p[kMaxN];
int n, travel_cost;
int GetDistance(int a, int b) {
    return abs(p[a].x - p[b].x) + abs(p[a].y - p[b].y);
}
int GetClosest(int node) {
    int where = -1;
    int mn =(int) 1e9;
    for (int i = 1; i <= n; i += 1) {   
        if (GetDistance(i, node) < mn && p[i].special) {
            where = i;
            mn = GetDistance(i, node);
        }
    }
    return where;
}
int sol[100];
int Solve(int a, int b) {
    int A = GetClosest(a);
    int B = GetClosest(b);
    if (A == -1) {
        return GetDistance(a, b);
    }
    return min(GetDistance(a, b), GetDistance(a, A) + travel_cost + GetDistance(B, b));
}
int main() {
    scanf("%d %d", &n, &travel_cost);
    for (int i = 1; i <= n; i += 1){
      scanf("%d %d %d", &p[i].special , &p[i].x , &p[i].y);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", Solve(a, b));
    }
    return 0;
}



















































