#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

bool*canEat(int*candiesCount, int candiesCountSz, int**queries, int queriesSz, int*queries0sz, int*rsz){
    int n = candiesCountSz;
    ll s[n+1]; clr(s);
    for(int i=0; i<n; ++i){
        s[i + 1] = s[i] + candiesCount[i];
    }
    bool*result=calloc(queriesSz, sizeof(bool));
    for(int z=0;z<queriesSz;z++){int*q = queries[z];
        ll min_s = s[q[0]] + 1;
        ll max_s = s[q[0] + 1];
        ll day = q[1];
        ll cap = q[2];
        ll min_t = day + 1;
        ll max_t = (day + 1) * cap;
        result[z] = (min_s <= max_t && max_s >= min_t);
    }
   *rsz=queriesSz;
    return result;
}
