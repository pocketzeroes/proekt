#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
/////////////////////////
typedef struct{
    int li, lj, ri, rj;
}Solution;

Solution newSolution( int li, int lj, int ri, int rj){
    Solution rez;
    rez.li = li;
    rez.lj = lj;
    rez.ri = ri;
    rez.rj = rj;
    return rez;
}
int cmpS(Solution a, Solution s){
    int diff = a.li - s.li;
    if(diff==0) diff = a.lj - s.lj;
    if(diff==0) diff = a.ri - s.ri;
    if(diff==0) diff = a.rj - s.rj;
    return diff;
}
void toString(Solution s){
    printf("%d %d %d %d\n", s.li, s.lj, s.ri, s.rj);
}

Solution solution;

void checkSolution( int r1, int c1, int r2, int c2 ){
    Solution newsol = newSolution(r1, c1, r2, c2);
    if(cmpS(newsol, solution) < 0)
        solution = newsol;
}
int main(){
    solution = newSolution(100, 100, 100, 100);
    int n = in_nextInt();
    int m = in_nextInt();
    char sheet[n][m];
    int paper = 0;
    getchar();
    for(int i=0; i<n; i++){
        for( int j=0; j<m; j++ ){
            sheet[i][j] = getchar();
            if(sheet[i][j]=='.' )
                ++paper;
        }
        getchar();
    }
    for( int i=1; i<n; i++ ){
        int  limit = min( i, n-i );
        bool found = true;
        int  count = 0;
        for( int j=0; j<m && found; j++ ){
            for( int k=0; k<limit && found; k++ ){
                ++count;
                found = (sheet[i+k][j]!=sheet[i-k-1][j]);
            }
        }
        if( found && count==paper )
            checkSolution( i, 1, i, m );
    }
    for( int j=1; j<m; j++ ){
        int limit = min( j, m-j );
        bool found = true;
        int count = 0;
        for( int i=0; i<n && found; i++ ){
            for( int k=0; k<limit && found; k++ ){
                ++count;
                found = (sheet[i][j+k]!=sheet[i][j-k-1]);
            }
        }
        if( found && count==paper )
            checkSolution( 1, j, n, j );
    }
    int max = n+m-3;
    for( int limit=1; limit<=max; ++limit ){
        int count = 0;
        bool found = true;
        for( int i=0; i<limit && found; i++ )
            for( int j=0; j<limit-i && found; j++ ){
                int newi = limit-j;
                int newj = limit-i;
                if( newi>=0 && newi<n && newj>=0 && newj<m ){
                    ++count;
                    found = (sheet[i][j]!=sheet[newi][newj]);
                }
            }
        int li=0, lj=0, ri=0, rj=0;
        if( limit<n ){
            li = limit+1;
            lj = 1;
        }
        else{
            li = n;
            lj = limit - n + 2;
        }
        if( limit<m ){
            ri = 1;
            rj = limit+1;
        }
        else{
            ri = limit - m + 2;
            rj = m;
        }
        if( found && count==paper )
            checkSolution( li, lj, ri, rj );
    }
    for( int limit=1; limit<=max; ++limit ){
        int count = 0;
        bool found = true;
        for( int i=0; i<limit && found; i++ ){
            for( int j=m-limit+i; j<m && found; j++ ){
                int newi = j-m+limit+1;
                int newj = m-limit+i-1;
                if( newi>=0 && newi<n && newj>=0 && newj<m ){
                    ++count;
                    found &= (sheet[i][j]!=sheet[newi][newj]);
                }
            }
        }
        int li=0, lj=0, ri=0, rj=0;
        if( limit<m ){
            li = 1;
            lj = m - limit;
        }
        else{
            li = limit - m + 2;
            lj = 1;
        }
        if( limit<n ){
            ri = limit+1;
            rj = m;
        }
        else{
            ri = n;
            rj = max - limit + 2;
        }
        if( found && count==paper )
            checkSolution( li, lj, ri, rj );
    }
    toString(solution);
    return 0;
}
