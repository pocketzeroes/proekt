#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

int main() {
    int n; 
    scanf("%d", &n);
    int first [n];memset(first ,0,sizeof(first ));
    int second[n];memset(second,0,sizeof(second));
    int closestPair(){
        int i, dif;
        qsort(first , n, sizeof(int), cmp);
        qsort(second, n, sizeof(int), cmp);
        i = 0;
        dif = abs(first[0] - second[0]);
        for(int z=0;z<n;z++){
            int e = first[z];
            while (i + 1 < n){
                if (second[i + 1] > e) 
                    break;
                i++;
            }
            dif = min(dif, abss(e - second[i]));
            if (i + 1 < n)
                dif = min(dif, abss(e - second[i + 1]));
        }
        return dif;
    }
    for (int i = 0; i < n; ++i) {
        int val; 
        scanf("%d", &val);
        first[i] = val;
    }
    for (int i = 0; i < n; ++i) {
        int val; 
        scanf("%d", &val);
        second[i] = val;
    }
    printf("%d\n", closestPair() );
    return 0;
}



















