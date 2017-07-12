#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

#define MOD (1000000007LL)



#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define check_pointer(p) if (!p) {puts("Out of memory."); exit(EXIT_FAILURE);}
#define MINIMUM_SIZE  1
#define GROWTH_FACTOR 2
typedef int T;

typedef struct
{
    T *bottom;
    T *top;
    T *allocated_top;
} 
stack;
 
stack * new(void)
{
  stack *s = malloc(sizeof(stack));
  check_pointer(s);
  s->bottom = malloc(MINIMUM_SIZE * sizeof(T));
  check_pointer(s->bottom);
  s->top = s->bottom - 1;
  s->allocated_top = s->bottom + MINIMUM_SIZE - 1;
  return s;
}
 
void destroy(stack *s)
{
  free(s->bottom);
  free(s);
}
 
bool empty(stack *s)
{
    return s->top < s->bottom ? true : false;
}
 
void push(stack *s, T x)
{
    if (s->top == s->allocated_top)
    {
        ptrdiff_t qtty = s->top - s->bottom + 1;
        ptrdiff_t new_qtty = GROWTH_FACTOR * qtty;
        s->bottom = realloc(s->bottom, new_qtty * sizeof(T));
        check_pointer(s->bottom);
        s->top = s->bottom + qtty - 1;
        s->allocated_top = s->bottom + new_qtty - 1;
    }
    *(++s->top) = x;
}
 
T pop(stack *s)
{
    return *(s->top--);
}
T top(stack *s)
{
    return *(s->top);
}


/////////////////////////
 
typedef long long ll;
enum{ N = 200005};
int n, arr[N], done[N], cyclic[N], DP[N], instack[N];
vec sizes;
stack*st;
int DP2[N], cnt_[N];

 
ll pwr(ll base, ll p, ll mod ){
  ll ans = 1;while(p){if(p&1)ans=(ans*base)%mod;base=(base*base)%mod;p/=2;}return ans;
}
ll gcd(ll a, ll b){
    if(b == 0)  return a;
    return gcd(b, a%b);
}
void dfs(int v){
    if(done[v]) return;
    done[v] = instack[v] = 1;
    push(st, v);
    if(!done[arr[v]]){
        dfs(arr[v]);
    }
    else if(instack[arr[v]]){
        int sz = 1;
        while(!empty(st) && top(st) != arr[v]){
            cyclic[top(st)] = 1;
            instack[top(st)] = 0;
            pop(st);
            sz++;
        }
        sizes.ptr = pushback(sizes.ptr, &sizes.sz ,sz);
        cyclic[arr[v]] = 1;
        instack[arr[v]] = 0;
        pop(st);
    }
    if(!empty(st) && top(st) == v){
        instack[v] = 0;
        pop(st);
    }
}
int dp(int v){
    if(cyclic[v])   
        return 0;
    int ans = DP[v];
    if(ans != -1)   
        return ans;
    ans = 1 + dp(arr[v]);
    DP[v]=ans;
    return ans;
}
int calc(int sz){
    if(DP2[sz] != -1)   
        return DP2[sz];
    if(sz == 1) 
        return 1;
    int ans = 1;
    ll val = 2;
    while(val % sz != 1){
        val = (val * 2) % sz;
        ans++;
    }
    return DP2[sz] = ans;
}
int main(){
    st=new();
    scanf("%d", &n);
    for(int i=1;i<=n;i++)  
        scanf("%d", &arr[i]);
    for(int i=1;i<=n;i++)
        dfs(i);
    memset(DP, -1, sizeof(DP));
    int ans = 0;
    for(int i=1;i<=n;i++){
        int temp = dp(i), x = 0;
        while(temp > 1){
            temp = (temp+1)/2;
            x++;
        }
        ans = max(ans, x);
    }
    memset(DP2, -1, sizeof(DP2));
    for(int q=0;q<sizes.sz; q++){int it = sizes.ptr[q];
        int z = it, cnt = 0;
        while(z % 2 == 0){
            z /= 2;
            cnt++;
        }
        ans = max(ans, cnt);
        int temp = calc(z);
        for(ll i=2;i*i<=temp;i++)
            if(temp%i==0){
                int z = 0;
                while(temp % i == 0){
                    temp /= i;
                    z++;
                }
                cnt_[i] = max(cnt_[i], z);
            }
        if(temp != 1)
            cnt_[temp] = max(cnt_[temp], 1);
    }
    ll lcm = 1;
    for(int i=2;i<N;i++)
        lcm = (lcm * pwr(i, cnt_[i], MOD)) % MOD;
    printf("%lld\n", (ans+lcm)%MOD);
    return 0;
}


















































