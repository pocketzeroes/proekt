#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
void fill(bool*arr, int sz, bool val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

bool nedges   [100][100];
bool cedges   [100][100];
int  color    [100];
int  component[100];
int  dists    [100][100];
int n;
int c;

void group( int k ){
    component[k] = c;
    for( int i=0; i<n; i++ ){
        if( nedges[i][k] ){
            if( component[i]<0 && color[i]==color[k] )
                group( i );
            else if( component[i]>=0 && color[i]!=color[k] )
                cedges[component[i]][c] = cedges[c][component[i]] = true;
        }
    }
}
int fw(){
    for( int i=0; i<c; i++ ){
        dists[i][i] = 0;
        for( int j=i+1; j<c; j++ )
            dists[i][j] = dists[j][i] = (cedges[i][j] ? 1 : 1000);
    }
    for( int k=0; k<c; k++ ){
        for( int i=0; i<c; i++ ){
            for( int j=0; j<c; j++ ){
                int d = dists[i][k] + dists[k][j];
                if( d<dists[i][j] )
                    dists[i][j] = d;
            }
        }
    }
    int result = INT_MAX;
    for( int i=0; i<c; i++ ){
        int mx = 0;
        for( int j=0; j<c; j++ ){
            if( dists[i][j]>mx && dists[i][j]<1000 ) 
                mx = dists[i][j];
        }
        if( mx<result ) 
            result = mx;
    }
    return result;
}
int main(){
    for(;;){
        n = in_nextInt();
        int m = in_nextInt();
        if( n==0 ) 
            break;
        for( int i=0; i<n; i++ ){
            color[i] = in_nextInt();
            component[i] = -1;
            fill( nedges[i], 100, false );
            fill( cedges[i], 100, false );
        }
        for( int i=0; i<m; i++ ){
            int a = in_nextInt()-1;
            int b = in_nextInt()-1;
            nedges[a][b] = nedges[b][a] = true;
        }
        c = 0;
        for( int i=0; i<n; i++ ){
            if( component[i]<0 ){
                group( i );
                ++c;
            }
        }
        printf("%d\n", fw());
        break;
    }
    return 0;
}
