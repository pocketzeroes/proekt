#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>

typedef long double ld;


typedef struct{
    ld x, y, z;
}pt;
ld dist(pt p1, pt p2){
    return sqrtl(powl(p1.x-p2.x,2) + powl(p1.y-p2.y,2) + powl(p1.z-p2.z,2));
}
int main(){
    int n;
    scanf("%d", &n);
    pt v[n];
    for(int i=0; i<n; i++)
        scanf("%Lf %Lf %Lf", &v[i].x, &v[i].y, &v[i].z);
    ld d[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            d[i][j] = dist(v[i], v[j]);
    ld memo[1<<n][2][n];
    for(int i=0; i< 1<<n; i++)
    for(int j=0; j< 2   ; j++)
    for(int k=0; k< n   ; k++)memo[i][j][k] = LDBL_MAX;
    memo[0][1][0] = 0;
    for(int i = 1; i <1<<n; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < n; k++){

                int currsubset = i;
                int currportal = j;
                int currnode   = k;
                for(int l = 0; l < n; l++){
                    if(i & (1<<l)){
                        ld weight = d[k][l];
                        int prevsubset = currsubset ^ (1 << l);
                        if(j == 1){
                            if(memo[currsubset][currportal][currnode] > memo[prevsubset][currportal^1][l])
                               memo[currsubset][currportal][currnode] = memo[prevsubset][currportal^1][l];
                        }
                        if(memo[currsubset][currportal][currnode] > memo[prevsubset][currportal^1][l] + weight)
                           memo[currsubset][currportal][currnode] = memo[prevsubset][currportal^1][l] + weight;
                        if(memo[currsubset][currportal][currnode] > memo[prevsubset][currportal][l] + weight)
                           memo[currsubset][currportal][currnode] = memo[prevsubset][currportal][l] + weight;
                    }
                }
            }
        }
    }
    
    printf("%.9Lf\n", memo[(1<<n)-1][1][0] );
    return 0;
}


