#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int cmp (const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
typedef long long ll;
enum{mod =(int)1e9 + 7};
int maxSumRangeQuery(int*a, int aSz, int**r, int rSz, int*r0sz){
    int n = aSz;
    int c[n]; clr(c);
    for(int z=0;z<rSz;z++){int*tmp = r[z];
        c[tmp[0]]++;
        if(tmp[1] + 1 < n)
            c[tmp[1] + 1]--;
    }
    for(int i = 1; i < n; i++)
        c[i] += c[i - 1];
    qsort(a,aSz,sizeof(int),cmp);
    qsort(c,n,  sizeof(int),cmp);
    int res = 0;
    for(int i = 0; i < n; i++)
        res = (res + (ll)a[i] * c[i]) % mod;
    return res;
}
