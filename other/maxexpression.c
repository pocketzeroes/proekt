#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

typedef long long ll;
int cmpLL(const void*pa, const void*pb){
    ll*a =(ll*)pa;
    ll*b =(ll*)pb;
    return(*a < *b)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
    ll*output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    ll*ptr;
    int sz;
}vecl;
vecl newVecL(){
    vecl rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
ll accumulate(ll*arr, int sz){
  ll sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
void erase(vecl*v, int pos){
    for(int i=pos; i < v->sz-1; i++){
        v->ptr[i] = v->ptr[i+1];
    }
    (v->sz)--;
}
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
/////////////////////////////////-----------------------------------------------

char buff[100000];
int main(){
    int N, n[3];
    scanf("%d", &N);
    scanf("%s", &buff);
    scanf("%d %d %d", &n[0], &n[1], &n[2]);
    vecl pos = newVecL();
    vecl neg = newVecL();
    bool plus = true;
    int count = 1;
    strcat(buff, "+");
    char*S = strdup(buff);
    int S_length = strlen(S);
    for(size_t i=1; i<S_length; i+=2){
        switch(S[i]){
            case '+':{
                if(plus) pos.ptr = pushbackL(pos.ptr, &pos.sz, count);
                else     neg.ptr = pushbackL(neg.ptr, &neg.sz, count);
                count = 1, plus = true;
            }break;
            case '-':{
                if(plus) pos.ptr = pushbackL(pos.ptr, &pos.sz, count);
                else     neg.ptr = pushbackL(neg.ptr, &neg.sz, count);
                count = 1, plus = false;
            }break;
            case '*':{
                ++count;
            }break;
        }
    }
    ll ans = 0LL;
    qsort(pos.ptr, pos.sz, sizeof(ll), cmpLL);
    qsort(neg.ptr, neg.sz, sizeof(ll), cmpLL);
    int sink = 0;
    while(neg.sz>0 && n[0] > 0){
        sink += (int)neg.ptr[neg.sz-1] - 1;
        neg.sz--;
        n[0]--;
    }
    if(n[0] > 0){
        int rm0 = min(n[0], sink);
        n[0] -= rm0, sink -= rm0;
    }
    if(n[0] == 0){
        while(pos.sz>0){
            int pw2 = min((int)pos.ptr[pos.sz-1], n[2]);
            ans += (1LL << pw2);
            pos.sz--;
            n[2] -= pw2;
        }
        int rm2 = min(sink, n[2]);
        sink -= rm2;
        n[2] -= rm2;
        if(neg.sz>0){
            ll each[neg.sz];
            fill(each, neg.sz, 1);
            for(int i=0; n[2]>0; i=(i+1) % neg.sz)
                if(neg.ptr[i]>0)
                    each[i] <<= 1, --neg.ptr[i], --n[2];
            ans -= accumulate(each, neg.sz);
        }
    }
    else if(n[2] == 0){
        for(size_t i=0; i<pos.sz; ++i){
            int am0 = min((int)pos.ptr[i], n[1]);
            n[1] -= am0;
            if(am0 == pos.ptr[i])
                ++ans;
        }
    }
    else if(pos.sz>0 && n[1]+n[2] >= pos.ptr[0]){
        ll best  = 0LL,
           extra = 0LL;
        while(pos.sz>0 && n[1] + n[2] >= pos.ptr[0]){
            ll add  = 0LL;
            int i   = 0;
            int sum = 0, 
                n0  = n[0], 
                n1  = n[1], 
                n2  = n[2];
            while(n1 + n2 >= sum + pos.ptr[i])
                sum += pos.ptr[i++];
            for(int j=i-1; j>=0; --j)
                add += (1LL<<min(n2, (int)pos.ptr[j])), n2 -= min(n2, (int)pos.ptr[j]);
            best   = max(best, add + extra);
            int bj = -1;
            n2     = n[2];
            for(int j=0; j<pos.sz; ++j)
                if(n1+n2>=pos.ptr[j]&&(bj<0||min(n2,(int)pos.ptr[j])>min(n2,(int)pos.ptr[bj])||(min(n2,(int)pos.ptr[j])==min(n2,(int)pos.ptr[bj])&&pos.ptr[j]<pos.ptr[bj])))
                    bj = j;
            if(bj < 0)
                break;
            int ts = min(n2, (int)pos.ptr[bj]);
            extra += (1LL<<ts);
            n[2] = n2 = (n2 - ts);
            n[1] = n1 = (n1 - (pos.ptr[bj]-ts));
            erase(&pos, bj);                                     // vecErase EraseVec
            best = max(best, extra);
        }
        ans += best;
    }
    printf("%lld\n", ans);
    return 0;
}
