#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j){
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}
int cmpr(const void*b, const void*a){
   return ( *(int*)a - *(int*)b );
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;
const ll mod=1e9+7;

int find_min_next(int x){
    int ans = x+1;
    vec v=newVec();
    v.sz=0;
    while(x!=0){
        pb(v, x%10);
        x/=10;
    }
    qsort(v.ptr, v.sz, sizeof(int), cmpr);//rev
    do{
        if(v.ptr[0]!=0){
            int tx=0;
            for(int i=0; i<v.sz; i++)
                tx = tx*10+v.ptr[i];
            ans = fmin(ans, tx);
        }
    }while(next_permutation(v.ptr, v.sz));
    return ans;
}
int mp(int k){
    int mp10 = 9;
    int mp100 = mp10+1*10+9;
    int mp1000 = mp100+2*10+9;
    int mp10000 = mp1000+3*10+9;
    int mp100000 = mp10000+4*10+9;
    int mp1000000 = mp100000+5*10+9;
    int mp10000000 = mp1000000+6*10+9;
    int mp100000000 = mp10000000+7*10+9;
    int mp1000000000 = mp100000000+8*10+9;
    if(k==10)return mp10;
    else if(k==100)return mp100;
    else if(k==1000)return mp1000;
    else if(k==10000)return mp10000;
    else if(k==100000)return mp100000;
    else if(k==1000000)return mp1000000;
    else if(k==10000000)return mp10000000;
    else if(k==100000000)return mp100000000;
    else if(k==1000000000)return mp1000000000;
    return 0;
}

int get(int x){
    int tx=x;
    if(x<10)
        return x-1;
    if(mp(x))
        return mp(x);
    if(mp(x-1))
        return mp(x-1)+1;
    vec v=newVec();
    while(x!=0){
        pb(v, x%10);
        x/=10;
    }
    int ok=1;
    for(int i=0;i<v.sz-1;i++)
        if(v.ptr[i]!=0)
            ok=0;
    if(ok)
        return get(tx-1)+1;
    int ans =0,
        flag=0,
        tmp =1;
    for(int i=v.sz-1;i>0;i--){
        tmp*=10;
        if(v.ptr[i]==0)
            continue;
        if(v.ptr[i]==1)
            flag=1;
        ans+=v.ptr[i]+1;
    }
    ans--;
    if(flag)
        ans--;
    ans+=v.ptr[0];
    return ans+mp(tmp);
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int x;
        scanf("%d", &x);
        printf("%d\n", get(x));
    }
    return 0;
}
