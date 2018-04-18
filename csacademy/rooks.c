#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a, b) do{ int tmp; tmp = a; a = b; b = tmp; }while(0);

enum{ MAX_K =(int) 1e5};
int x[MAX_K],  y [MAX_K];
int x1[MAX_K], gy1[MAX_K], x2[MAX_K], y2[MAX_K];
int ux[MAX_K], uy[MAX_K];
int pq[MAX_K];
int pr[MAX_K];
enum{ B_SIZE = 170     };
enum{ MAX_N  = (int)3e4 + 10};
int f  [MAX_N];
int aib[MAX_N];

int cmp_q_x(const void*pa, const void*pb){
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int a=*ptra;
    int b=*ptrb;
    if ( x1[a] / B_SIZE == x1[b] / B_SIZE )
        return(x2[a] < x2[b])?-1:1;
    else
        return(x1[a] < x1[b])?-1:1;
}
int cmp_r_x(const void*pa, const void*pb){
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int a=*ptra;
    int b=*ptrb;
    return(x[a] < x[b])?-1:1;
}
void update(int y, int val){
    f[y] += val;
    int s = 0;
    if ( f[y] == 0 ) 
        s = -1;
    else if ( f[y] == 1 && val == 1 ) 
        s = 1;
    if ( s == 0 )
        return;
    while ( y < MAX_N ) {
        aib[y] += s;
        y += (y & -y);
    }
}
int query(int y){
    int s = 0;
    while ( y > 0 ) {
        s += aib[y];
        y -= ( y & -y );
    }
    return s;
}
int main(){
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);
    for ( int i = 0; i < k; i++ ) {
        scanf("%d %d", &x[i], &y[i]);
        pr[i] = i;
    }
    qsort(pr, k, sizeof(int), cmp_r_x);
    for ( int i = 0; i < q; i++ ) {
        scanf("%d %d %d %d", &x1[i], &gy1[i], &x2[i], &y2[i]);
        pq[i] = i;
    }
    qsort(pq, q, sizeof(int), cmp_q_x);
    int st = 0, dr = -1;
    for ( int i = 0; i < q; i++ ) {
        int t = pq[i];
        while ( dr < k - 1 && x2[t] >= x[pr[dr + 1]]) update( y[pr[++dr]], 1 );
        while ( st > 0 && x1[t] <= x[pr[st - 1]])     update( y[pr[--st]], 1 );
        while ( dr >= 0 && x2[t] < x[pr[dr]] )        update( y[pr[dr--]], -1 );
        while ( st < k && x1[t] > x[pr[st]] )         update( y[pr[st++]], -1 );
        ux[t] = query( y2[t] ) - query( gy1[t] - 1 );
    }
    for ( int i = 0; i < MAX_N; i++ )
        f[i] = aib[i] = 0;
    for ( int i = 0; i < k; i++ ) {
        swap(x[i], y[i]);
        pr[i] = i;
    }
    qsort(pr, k, sizeof(int), cmp_r_x);
    for ( int i = 0; i < q; i++ ) {
        swap(x1[i], gy1[i]);
        swap(x2[i], y2 [i]);
        pq[i] = i;
    }
    qsort(pq, q, sizeof(int), cmp_q_x );
    st = 0, dr = -1;
    for ( int i = 0; i < q; i++ ) {
        int t = pq[i];
        while ( dr < k - 1 && x2[t] >= x[pr[dr + 1]]) update( y[pr[++dr]], 1 );
        while ( st > 0 && x1[t] <= x[pr[st - 1]])     update( y[pr[--st]], 1 );
        while ( dr >= 0 && x2[t] < x[pr[dr]] )        update( y[pr[dr--]], -1 );
        while ( st < k && x1[t] > x[pr[st]] )         update( y[pr[st++]], -1 );
        uy[t] = query( y2[t] ) - query( gy1[t] - 1 );
    }
    for ( int i = 0; i < q; i++ ) {
        int dx = x2[i] - x1[i] + 1, dy = y2[i] - gy1[i] + 1;
        printf("%d\n", ux[i] * dy + uy[i] * dx - ux[i] * uy[i]);
    }
    return 0;
}

