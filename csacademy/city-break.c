#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

int d[111111];
ll ans;

int main(){
    int n, s;
    scanf("%d %d", &n, &s);
    for(int i = 0; i < n; i++)
        scanf("%d", &d[i]);
    s--;
    pair l = newPair((s+n-1)%n,d[(s+n-1)%n]);
    pair r = newPair((s+1)%n,d[(s)%n]);
    for(int i=0; i<n-1; i++){
        if(l.second<r.second){
            ans+=l.second;
            r.second+=l.second;
            l.second=d[(l.first+n-1)%n];
            l.first=(l.first+n-1)%n;
        }
        else if(l.second>r.second){
            ans+=r.second;
            l.second+=r.second;
            r.second=d[(r.first)%n];
            r.first=(r.first+1)%n;
        }
        else{
            if(l.first<r.first){
                ans+=l.second;
                r.second+=l.second;
                l.second=d[(l.first+n-1)%n];
                l.first=(l.first+n-1)%n;
            }
            else{
                ans+=r.second;
                l.second+=r.second;
                r.second=d[(r.first)%n];
                r.first=(r.first+1)%n;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
