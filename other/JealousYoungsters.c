#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
///////////////////////////

int main(){
    int n = in_nextInt();
    int m = in_nextInt();
    if(m < n){
        puts("impossible");
        return 0;
    }
    int b = in_nextInt()+1;
    int r = in_nextInt();
    int start[n][n]; clr(start);
    int first[n][n]; clr(first);
    int total[n][n]; clr(total);
    int pref [n][n]; clr(pref );
    int pos[n]; clr(pos);
    int cur[n]; clr(cur);
    while(r-- > 0){
        int s = in_nextInt()+1;
        int k = in_nextInt()-1;
        int t = in_nextInt()-1;
        if(start[k][cur[k]] != 0){
            total[k][cur[k]] += s-start[k][cur[k]];
            start[k][cur[k]] = 0;
        }
        if(t == -1 || t >= n)
            continue;
        cur[k] = t;
        start[k][t] = s;
        if(first[k][t] == 0){
            first[k][t] = s;
            pref[k][pos[k]++] = t;
        }
    }
    for(int k=0; k<n; k++){
        for(int t=0; t<n; t++){
            if(first[k][t] == 0)
                pref[k][pos[k]++] = t;
            if(start[k][t] != 0)
                total[k][t] += b-start[k][t];
        }
    }
    int toy[n]; clr(toy);
    int who[n];
    for(int i=0; i<n; i++){
        who[i] =-1;
        pos[i] = 0;
    }
    for(int i=0; i<n; i++){
        int x = i;
        while(x != -1){
            int p = pref[x][pos[x]];
            if(who[p] == -1 || total[x][p] < total[who[p]][p]){
                int old = who[p];
                who[p] = x;
                toy[x] = p;
                x = old;
            }
            else
                pos[x]++;
        }
    }
    for(int i=0; i<n; i++)
        printf("%d ", (toy[i]+1));
    puts("");
    return 0;
}
