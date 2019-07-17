#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

void fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

typedef struct{
    int x, y, z;
}pt;
pt newpt(int x, int y, int z){
    pt rez;
    rez.x = x;
    rez.y = y;
    rez.z = z;
    return rez;
}
double distance(pt a, pt p){
    double dx = p.x - a.x;
    double dy = p.y - a.y;
    double dz = p.z - a.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double memo [14][1<<15];
double dists[15][15];
int target;
int npoints;

double best( int node, int state){
    if( memo[node][state]<0.0 ){
        if( state==target )
            memo[node][state] = dists[node][0];
        else{
            double bestsofar = DBL_MAX;
            for( int i=1; i<=npoints; i++ )
                if( (state&(1<<i))==0 )
                    bestsofar = min( bestsofar, dists[node][i] + best( i, state|(1<<i) ) );
            memo[node][state] = bestsofar;
        }
    }
    return memo[node][state];
}
double*allbests(int k){
    double*bests = calloc(k, sizeof(double));
    npoints = k;
    target = ((1<<npoints)-1)<<1;
    for( int i=0; i<=npoints; i++ )
        fill( memo[i], 1<<15, -1.0);
    for( int i=1; i<=npoints; i++ )
        bests[i-1] = best( i, 1<<i );
    return bests;
}
int main(){
    for(;;){
        int n = in_nextInt();
        int x = in_nextInt();
        int y = in_nextInt();
        int z = in_nextInt();
        if( n==0 )
            break;
        pt start = newpt(x, y, z);
        pt switches[n]; memset(switches, 0, sizeof(switches));
        pt*coins[n]; memset(coins, 0, sizeof(coins));
        double*bests[n]; memset(bests, 0, sizeof(bests));
        int bestszs[n]; memset(bestszs, 0, sizeof(bestszs));
        for(int s=0; s<n; s++){
            int k = in_nextInt();
            x = in_nextInt();
            y = in_nextInt();
            z = in_nextInt();
            switches[s] = newpt(x, y, z);
            coins[s] = calloc(k, sizeof(pt));
            for(int c=0; c<k; c++){
                x = in_nextInt();
                y = in_nextInt();
                z = in_nextInt();
                coins[s][c] = newpt( x, y, z );
            }
            dists[0][0] = 0.0;
            for( int i=1; i<=k; i++ ){
                dists[0][i] = dists[i][0] = distance(switches[s], coins[s][i-1]);
                for( int j=i; j<=k; j++ )
                    dists[i][j] = dists[j][i] = distance(coins[s][i-1], coins[s][j-1]);
            }
            bests[s] = allbests( k );
            bestszs[s]=k;
        }
        dists[0][0] = 0.0;
        double mn;
        for( int i=1; i<=n; i++ ){
            dists[i][0] = dists[0][i] = distance(start, switches[i-1] );
            dists[i][i] = 0.0;
            for( int j=1; j<=n; j++ ){
                if( j!=i ){
                    mn = DBL_MAX;
                    for(int b=0; b<bestszs[j-1]; b++)
                        mn = min( mn, distance(switches[i-1], coins[j-1][b] ) + bests[j-1][b]);
                    dists[i][j] = mn;
                }
            }
        }
        double*results = allbests( n );
        double answer = DBL_MAX;
        for(int i=0; i<n; i++){
            mn = DBL_MAX;
            for(int j=0; j<bestszs[i]; j++)
                mn = min(mn, bests[i][j] );
            answer = min( answer, results[i]+mn);
        }
        printf("%.6lf\n", answer);
        break;
    }
    return 0;
}
