#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
char buff[100001];
char*getln(){
  char*rv = gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

char*s;
int  n;
int**P;
int psz;


void compress(){ //puts(__FUNCTION__);
    int cnt[256]; clr(cnt);
//puts("for1");
    for(int i=0; i<n; ++i)
        cnt[s[i]]++;
//puts("for2");
    for(int i=0, mp=0; i<256; ++i)
        if(cnt[i]>0)
           cnt[i]=mp++;
//puts("for3");
    for(int i=0; i<n; ++i)
        P[0][i]=cnt[s[i]];

//    puts("done");
}
void construct(){//puts(__FUNCTION__);
    P    = calloc(n, sizeof(int*));
    P[psz++] = calloc(n, sizeof(int ));
    compress();
    int occ[n+1]; clr(occ);
    int s1 [n  ]; clr(s1 );
    int s2 [n  ]; clr(s2 );
    for(int k=1, cnt=1; cnt/2<n; ++k, cnt*=2){
        P[psz++] = calloc(n, sizeof(int));
        for(int i=0; i<=n; ++i)
            occ[i] = 0;
        for(int i=0; i<n; ++i)
            occ[i+cnt<n?P[k-1][i+cnt]+1:0]++;
        for(int i=0, sum=0, t; i<=n; ++i){
            t = occ[i];
            occ[i] = sum;
            sum += t;
        }
        for(int i=0; i<n; ++i)
            s1[occ[i+cnt<n?P[k-1][i+cnt]+1:0]++] = i;
        for(int i=0; i<=n; ++i)
            occ[i] = 0;
        for(int i=0; i<n; ++i)
            occ[P[k-1][s1[i]]]++;
        for(int i=0, sum=0, t; i<=n; ++i){
            t = occ[i];
            occ[i] = sum;
            sum += t;
        }
        for(int i=0; i<n; ++i)
            s2[occ[P[k-1][s1[i]]]++] = s1[i];
        for(int i=0, p1=-3, p2=-3; i<n; ++i){
            P[k][s2[i]] = (P[k-1][s2[i]] != p1 || (s2[i]+cnt<n?P[k-1][s2[i]+cnt]:-1) != p2) ? i : P[k][s2[i - 1]];
            p1 = P[k-1][s2[i]];
            p2 = s2[i]+cnt<n?P[k-1][s2[i]+cnt]:-1;
        }
    }
}
int main(){//puts(__FUNCTION__);
    while((s=getln())!=NULL){
        n = strlen(s);
        construct();
        int inv[n]; fill(inv, n, -1);
        int*arr = P[psz-1];
        for(int i=0; i<n; ++i)
            inv[arr[i]] = i;
        int q;
        scanf("%d", &q);
        for(int c=0; c<q; ++c){
            int x;
            scanf("%d", &x);
            printf("%d ", inv[x]);
        }
        puts("");
        getchar();
        free(s);
        n=0;
        for(int i=0;i<psz;i++)
            free(P[i]);
        free(P); P=NULL;
        psz=0;
    }
    return 0;
}
