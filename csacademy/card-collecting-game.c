#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#if 1 //map
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
struct Pair {
    int key;
    int value;
};
typedef struct Pair Pair;
struct Bucket {
    unsigned int count;
    Pair *pairs;
};
typedef struct Bucket Bucket;
struct IntMap {
    unsigned int count;
    Bucket *buckets;
};
typedef struct IntMap IntMap;

unsigned int hash(unsigned int key);
static Pair * get_pair(Bucket *bucket, int key);

IntMap * sm_new(unsigned int capacity){
    IntMap *map;
    map = malloc(sizeof(IntMap));
    if (map == NULL) {
        return NULL;
    }
    map->count = capacity;
    map->buckets = malloc(map->count * sizeof(Bucket));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }
    memset(map->buckets, 0, map->count * sizeof(Bucket));
    return map;
}
void sm_delete(IntMap *map){
    unsigned int i, j, n, m;
    Bucket *bucket;
    Pair *pair;
    if (map == NULL) {
        return;
    }
    n = map->count;
    bucket = map->buckets;
    i = 0;
    while (i < n) {
        m = bucket->count;
        pair = bucket->pairs;
        j = 0;
        while(j < m) {
            pair++;
            j++;
        }
        free(bucket->pairs);
        bucket++;
        i++;
    }
    free(map->buckets);
    free(map);
}

int sm_get(const IntMap *map, int key, int*out){
    unsigned int index;
    Bucket *bucket;
    Pair *pair;
    if (map == NULL)
        return 0;
    index = hash(key) % map->count;
    bucket = &(map->buckets[index]);
    pair = get_pair(bucket, key);
    if (pair == NULL)
        return 0;
   *out = pair->value;
    return 1;
}

int sm_exists(const IntMap *map, int key){
    unsigned int index;
    Bucket *bucket;
    Pair *pair;
    if (map == NULL) {
        return 0;
    }
    index = hash(key) % map->count;
    bucket = &(map->buckets[index]);
    pair = get_pair(bucket, key);
    if (pair == NULL) {
        return 0;
    }
    return 1;
}
int sm_put(IntMap *map, int key, int value){
    unsigned int key_len, value_len, index;
    Bucket *bucket;
    Pair *tmp_pairs, *pair;
    int tmp_value;
    int  new_key, new_value;
    if (map == NULL) {
        return 0;
    }
    index = hash(key) % map->count;
    bucket = &(map->buckets[index]);
    if ((pair = get_pair(bucket, key)) != NULL) {
        pair->value = value;
        return 1;
    }
    if (bucket->count == 0) {
        bucket->pairs = malloc(sizeof(Pair));
        if (bucket->pairs == NULL) {
            return 0;
        }
        bucket->count = 1;
    }
    else {
        tmp_pairs = realloc(bucket->pairs, (bucket->count + 1) * sizeof(Pair));
        if (tmp_pairs == NULL) {
            return 0;
        }
        bucket->pairs = tmp_pairs;
        bucket->count++;
    }
    pair = &(bucket->pairs[bucket->count - 1]);
    pair->key   = key;
    pair->value = value;
    return 1;
}
int sm_get_count(const IntMap *map){
    unsigned int i, j, n, m;
    unsigned int count;
    Bucket *bucket;
    Pair *pair;
    if (map == NULL) {
        return 0;
    }
    bucket = map->buckets;
    n = map->count;
    i = 0;
    count = 0;
    while (i < n) {
        pair = bucket->pairs;
        m = bucket->count;
        j = 0;
        while (j < m) {
            count++;
            pair++;
            j++;
        }
        bucket++;
        i++;
    }
    return count;
}
int sm_enum(const IntMap *map){
    unsigned int i, j, n, m;
    Bucket *bucket;
    Pair *pair;
    if (map == NULL) {
        return 0;
    }
    bucket = map->buckets;
    n = map->count;
    i = 0;
    while (i < n) {
        pair = bucket->pairs;
        m = bucket->count;
        j = 0;
        while (j < m) {
            //enum_func(pair->key, pair->value, obj);
            printf("key=[%d] value=[%d]\n", pair->key, pair->value);
            pair++;
            j++;
        }
        bucket++;
        i++;
    }
    return 1;
}
static Pair * get_pair(Bucket *bucket, int key){
    unsigned int i, n;
    Pair *pair;
    n = bucket->count;
    if (n == 0) {
        return NULL;
    }
    pair = bucket->pairs;
    i = 0;
    while (i < n) {
        if (pair->key == key) {
            return pair;
        }
        pair++;
        i++;
    }
    return NULL;
}
unsigned int hash(unsigned int key){
    key += (key << 12);
    key ^= (key >> 22);
    key += (key << 4);
    key ^= (key >> 9);
    key += (key << 10);
    key ^= (key >> 2);
    key += (key << 7);
    key ^= (key >> 12);
    key = (key >> 3) * 2654435761;
    return key;
}
#endif
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}
enum{ MAXN       = 2000  };
enum{ MAXNEEDSUM = 2000  };
enum{ MAXSUM     = 500000};
typedef struct Card_s{
    int need;
    int cnt;
    int points;
}Card;
int cmpC(const void*pa, const void*pb){
    Card*a=(Card*)pa;
    Card*b=(Card*)pb;
    return (a->points > b->points)?-1:1;
}
int n;
Card card[MAXN];
int sum, hsum;
int dp1[2][4*MAXNEEDSUM+1][2][2];
IntMap*cntfull;
int dp2[2][MAXSUM/2+1];
int main(){
    IntMap*cntfull = sm_new(10);
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%d %d %d", &card[i].need, &card[i].cnt, &card[i].points);
    qsort(card, n, sizeof(Card), cmpC);
    sum = 0;
    for(int i=0; i<n; ++i)
        sum += card[i].cnt;
    hsum = sum/2;
    ll extra = 0;
    int at1 = 0, needsum = 0;
    memset(dp1[at1], -1, sizeof(dp1[at1]));
    dp1[at1][0][0][0] = 0;
    for(int i=0; i<n; ++i){
        memset(dp1[1-at1], -1, sizeof(dp1[1-at1]));
        needsum += card[i].need;
        int lim  = min(card[i].cnt,2*card[i].need-1);
        int full = card[i].cnt-lim-(card[i].cnt-lim)%(2*card[i].need);
        int fullcnt = full/(2*card[i].need);
        if(fullcnt>0){
            int val=0;
            sm_get(cntfull, 2*card[i].need,&val);
            sm_put(cntfull, 2*card[i].need, val+fullcnt);
            extra += (ll)fullcnt*card[i].points;
        }
        for(int j=0; j<=4*needsum; ++j)
            for(int p1=0; p1<2; ++p1)
                for(int p2=0; p2<2; ++p2){
                    for(int k1=0; k1<=lim; ++k1){
                        int k2 = (card[i].cnt-k1)%(2*card[i].need),pp1=p1,pp2=p2,delta=0,jj=j-k1,kk=k1+k2;
                        int curfullcnt = (card[i].cnt-kk-full)/(2*card[i].need);
                        delta += curfullcnt*card[i].points;
                        if(k1==2*card[i].need-1) {
                            pp1=1-pp1;
                            if(pp1==0)
                                delta += card[i].points;
                        }
                        if(k2 == 2 * card[i].need-1) {
                            pp2 = 1-pp2;
                            if(pp2 == 1)
                                delta += card[i].points;
                        }
                        for(int dj=0; dj<=(curfullcnt); ++dj){
                            if(dj==1)
                                jj-=2*card[i].need;
                            if(jj<0 || dp1[at1][jj][pp1][pp2] == -1)
                                continue;
                            dp1[1-at1][j][p1][p2] = max(dp1[1-at1][j][p1][p2],
                                                        dp1[at1][jj][pp1][pp2]+delta);
                        }
                    }
                }
        at1 = 1-at1;
    }
    int at2 = 0, fullsum=0;
    memset(dp2[at2], -1, sizeof(dp2[at2]));
    dp2[at2][0] = 0;

    unsigned int i, jjj, n, m;
    Bucket *bucket;
    Pair *pair;
    bucket = cntfull->buckets;
    n      = cntfull->count;
    i = 0;
    while (i < n) {
        pair = bucket->pairs;
        m    = bucket->count;
        jjj  = 0;
        while (jjj < m) {
            int cursz = pair->key, curcnt = pair->value;
            fullsum += cursz*curcnt;
            int lim = min(fullsum, hsum);
            memset(dp2[1-at2], -1, sizeof(dp2[1-at2]));
            for(int j=0; j<=lim; ++j){
                if(dp2[at2  ][j]!=-1)
                   dp2[1-at2][j] = 0;
                else if(j>=cursz && dp2[1-at2][j-cursz]!=-1 && dp2[1-at2][j-cursz]<curcnt)
                    dp2[1-at2][j] = dp2[1-at2][j-cursz]+1;
            }
            at2 = 1-at2;

            pair++;
            jjj++;
        }
        bucket++;
        i++;
    }

    ll ret = -1;
    for(int j=0; j<=4*needsum; ++j)
        for(int p1=0; p1<2; ++p1)
            for(int p2=0; p2<2; ++p2){
                if(dp1[at1][j][p1][p2] == -1 || j>hsum)
                    continue;
                int rem = hsum-j;
                if(rem>fullsum || dp2[at2][rem] == -1)
                    continue;
                ret=max(ret, extra + dp1[at1][j][p1][p2]);
            }
    printf("%lld\n", ret);
}