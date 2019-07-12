#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
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
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
void reverse(ll*nums, int start, int end){
    while( start < end){
        swap(nums[start], nums[end]);
        start++;
        end  --;
    }
}


vecl convert(ll n, ll b){
    vecl ans = newVecL();
    while(n){
        ans.ptr = pushbackL(ans.ptr, &ans.sz, n%b);
        n /= b;
    }
    reverse(ans.ptr, 0, ans.sz-1);
    return ans;
}
bool palindrome(vecl n){
    for(ll i = 0, j = n.sz-1; i < n.sz; ++i, --j)
        if(n.ptr[i] != n.ptr[j])
            return false;
    return true;
}
int main(){
    ll a, b, k;
    scanf("%lld%lld%lld", &a, &b, &k);
    ll count = 0;
    for(ll i = a; i <= b; ++i){
        bool works = true;
        for(ll j = 2; j <= k && works; ++j)
            works = works && palindrome(convert(i, j));
        if(works)
            ++count;
    }
    printf("%lld\n", count);
    return 0;
}
