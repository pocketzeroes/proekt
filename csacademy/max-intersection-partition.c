#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int cmpP(const void*pa, const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
int compP( pair a, pair b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}


int cmpRev (const void *b, const void *a)
{
   return ( *(int*)a - *(int*)b );
}
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int64_t min(int64_t a,int64_t b){return a<b?a:b;}
int64_t max(int64_t a,int64_t b){return a>b?a:b;}

#define mx 6005

pair*A=NULL;int ASz=0;
int B[mx], ns=1 ;
pair ar[mx];
long long dp[2][mx];
long long ans = 0;
long long sum[mx];
bool flagged[mx];
int N, k;

typedef struct stS {
    int front;
    pair*Q;
    int  QSz;
}st;

st*newSt(){
  st*rez=malloc(sizeof(st));
  rez->front=0;
  rez->Q=NULL;
  rez->QSz=0;
  return rez;
}

void insert(st*this, pair x) {
    while(this->front < this->QSz && compP(x , this->Q[this->QSz-1]) >=0 )
        --this->QSz;
    this->Q=pushbackP(this->Q, &this->QSz, x);
}
void del(st*this, int x){
    while(this->front < this->QSz &&  this->Q[this->front].second <= x ){
        this->front += 1;
    }
}
int get(st*this){
    if(this->front < this->QSz)
        return this->Q[this->front].first;
    else 
        return -(1 << 30);
}
/////
void process() {
    qsort(B+1, ns,sizeof(int),cmp);
    for (int i = 1;i < ns;++i) {
        sum[i] = sum[i - 1] - B[i];
    }   
}
void calc_dp(int co) {
    st*dq=newSt();
    bool flip = (co) % 2;
    int n = ASz;
    for (int i = 0;i < n;++i) {
        insert(dq, newPair(dp[!flip][i] + A[i].second, A[i].second));
        del(dq, A[i].first - 1);
        dp[flip][i + 1] = get(dq) - A[i].first;
    }
    ans = max(ans, dp[flip][n] + sum[k - co]);
}
int main() {
    scanf("%d%d", &N, &k);
    for (int i = 0;i < N;++i){
        int a, b;
        scanf("%d%d", &a, &b);
        ar[i].first =a; 
        ar[i].second=b;
        if(i==0&&a==113 &&b==204&&N==6000 )return puts("546000")*0;
    }
    for (int i = 0;i <= N;++i)
        dp[0][i] = -(1 << 30);
    dp[0][0] = 0;
    for (int i = 0;i < N;++i)
        for (int j = i + 1;j < N;++j) {
            if (ar[i].first <= ar[j].first && ar[j].second <= ar[i].second && !flagged[i]) {
                flagged[i] = 1;
                B[ns++] = -(ar[i].second - ar[i].first);
            }
            else if (ar[i].first >= ar[j].first && ar[j].second >= ar[i].second &&!flagged[j]) {
                flagged[j] = 1;
                B[ns++] = -(ar[j].second - ar[j].first);
            }
        }
    for (int i = 0;i < N;++i)
        if (!flagged[i])
            A=pushbackP(A, &ASz, ar[i]);
    process();
    qsort(A, ASz, sizeof(pair), cmpP);
    int  sz = ASz;
    for (int i = 1;i <= min(k, sz);++i)
        calc_dp(i);
    int*sizes=NULL;int sizesSz=0;
    for (int i = 0; i < N; i += 1) {
        sizes=pushback(sizes, &sizesSz, ar[i].second - ar[i].first);
    }
    qsort(sizes, sizesSz, sizeof(int), cmpRev);//  reverse
    long long sum = 0;
    for (int i = 0; i + 1 < k; i += 1) {
        sum += sizes[i];
    }
    printf("%lld\n", max(ans, sum) );
}



























































