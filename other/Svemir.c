#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAXN = 100100};
int n;
typedef struct planet{
    int x, y, z, index;
}planet;
planet P[ MAXN ], Org[ MAXN ]; 

int cmpP(const void*pa, const void*pb){
    planet*A=(planet*)pa;
    planet*B=(planet*)pb;
    if(A->x != B->x) return(A->x < B->x)?-1:1;
    if(A->y != B->y) return(A->y < B->y)?-1:1;
    if(A->z != B->z) return(A->z < B->z)?-1:1;
    return 0;
}
int x_cmpf(const void*pa, const void*pb){
    planet*A=(planet*)pa;
    planet*B=(planet*)pb;
    return(A->x < B->x)?-1:1;
}
int y_cmpf(const void*pa, const void*pb){
    planet*A=(planet*)pa;
    planet*B=(planet*)pb;
    return(A->y < B->y)?-1:1;
}
int z_cmpf(const void*pa, const void*pb){
    planet*A=(planet*)pa;
    planet*B=(planet*)pb;
    return(A->z < B->z)?-1:1;
}

int dist(planet*A, planet*B){
    return fmin(abs(A->x-B->x ), fmin( abs( A->y-B->y ), abs( A->z-B->z ) ) );
}

typedef struct edge{
    int ind_a, ind_b, cost;
}edge;
edge newedge(int a, int b){
    return(edge){a, b, dist(&Org[a], &Org[b])};
}
int cmpE(const void*pa, const void*pb){
    edge*A=(edge*)pa;
    edge*B=(edge*)pb;
    return(A->cost < B->cost)?-1:1;
}
edge*E;
int dad[ MAXN ];

int find_dad( int x ){
    if( dad[x] == -1 ) 
        return x;
    return dad[x] = find_dad( dad[x] );
}
int main(){
    scanf("%d", &n);
    E = calloc( 3*n + 100, sizeof(edge));
    int esz = 0;
    for(int i=0; i<n; ++i){
        scanf("%d %d %d", &P[i].x, &P[i].y, &P[i].z );
        P[i].index = i;
        Org[i] = P[i];
    }
    qsort(P, n, sizeof(planet), cmpP);

    qsort(P, n, sizeof(planet), x_cmpf); for(int i=1; i<n; ++i) E[esz++] = newedge(P[i-1].index, P[i].index);
    qsort(P, n, sizeof(planet), y_cmpf); for(int i=1; i<n; ++i) E[esz++] = newedge(P[i-1].index, P[i].index);
    qsort(P, n, sizeof(planet), z_cmpf); for(int i=1; i<n; ++i) E[esz++] = newedge(P[i-1].index, P[i].index);
    qsort(E, esz, sizeof(edge), cmpE);
    ll sum = 0;
    memset(dad, -1, sizeof(dad));
    for(int z=0; z<3*n; z++){
        int A = find_dad(E[z].ind_a);
        int B = find_dad(E[z].ind_b);
        if(A != B){
            sum += E[z].cost;
            dad[A] = B;
        }
    }
    printf("%lld\n", sum);
    return 0;
}
