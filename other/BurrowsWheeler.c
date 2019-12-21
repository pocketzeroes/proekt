#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000001];
char*getln(){
  char*rv = gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}


enum{ MAX_N = 200010};
char T[MAX_N];
int n;
int RA[MAX_N], tempRA[MAX_N];
int SA[MAX_N], tempSA[MAX_N];
int c[MAX_N];
char P[MAX_N];
int m;
int Phi[MAX_N];
int PLCP[MAX_N];
int LCP[MAX_N];

int cmp(const void*pa, const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return(strcmp(T+ *a, T+ *b)<0)?-1:1;
}
void constructSA_slow(){
  for(int i = 0; i < n; i++)
    SA[i] = i;
  qsort(SA, n, sizeof(int), cmp);
}
void countingSort(int k){
  int i, sum, maxi = fmax(300, n);
  memset(c, 0, sizeof c);
  for(i = 0; i < n; i++)
    c[i + k < n ? RA[i + k] : 0]++;
  for(i = sum = 0; i < maxi; i++){
    int t = c[i];
    c[i] = sum;
    sum += t;
  }
  for (i = 0; i < n; i++)
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; i++)
    SA[i] = tempSA[i];
}
void constructSA(){
  int i, k, r;
  for (i = 0; i < n; i++)
    RA[i] = T[i];
  for (i = 0; i < n; i++)
    SA[i] = i;
  for (k = 1; k < n; k <<= 1) {
    countingSort(k);
    countingSort(0);
    tempRA[SA[0]] = r = 0;
    for (i = 1; i < n; i++)
      tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++)
      RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) 
      break;
  }
}
void computeLCP_slow(){
  LCP[0] = 0;
  for (int i = 1; i < n; i++) {
    int L = 0;
    while (T[SA[i] + L] == T[SA[i-1] + L]) 
      L++;
    LCP[i] = L;
  }
}
void computeLCP(){
  int i, L;
  Phi[SA[0]] = -1;
  for (i = 1; i < n; i++)
    Phi[SA[i]] = SA[i-1];
  for (i = L = 0; i < n; i++){
    if (Phi[i] == -1){
      PLCP[i] = 0; 
      continue; 
    }
    while (T[i + L] == T[Phi[i] + L]) 
      L++;
    PLCP[i] = L;
    L = fmax(L-1, 0);
  }
  for (i = 0; i < n; i++)
    LCP[i] = PLCP[SA[i]];
}
pair stringMatching(){
  int lo = 0, hi = n-1, mid = lo;
  while (lo < hi){
    mid = (lo + hi) / 2;
    int res = strncmp(T + SA[mid], P, m);
    if (res >= 0) 
      hi = mid;
    else 
      lo = mid + 1;
  }
  if (strncmp(T + SA[lo], P, m) != 0) 
    return newpair(-1, -1);
  pair ans; 
  ans.first = lo;
  lo = 0; 
  hi = n - 1; 
  mid = lo;
  while (lo < hi){
    mid = (lo + hi) / 2;
    int res = strncmp(T + SA[mid], P, m);
    if (res > 0) 
      hi = mid;
    else 
      lo = mid + 1;
  }
  if(strncmp(T + SA[hi], P, m) != 0) 
    hi--;
  ans.second = hi;
  return ans;
}
pair LRS(){
  int i, idx = 0, maxLCP = -1;
  for (i = 1; i < n; i++)
    if (LCP[i] > maxLCP)
      maxLCP = LCP[i], idx = i;
  return newpair(maxLCP, idx);
}
int owner(int idx){
  return (idx < n-m-1) ? 1 : 2; 
}
pair LCS(){
  int i, idx = 0, maxLCP = -1;
  for (i = 1; i < n; i++)
    if (owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP)
      maxLCP = LCP[i], idx = i;
  return newpair(maxLCP, idx);
}
int main(){
  char*ln;
  while((ln=getln())!=NULL){
    n = strlen(ln);
    strcpy(T, ln);
    strcat(T, ln);
    n *= 2;
    T[n++] = '\0';
    constructSA();
    for(int i=0; i<n; i++){
      if(SA[i]<n/2)
        printf("%c", T[SA[i] + n/2 - 1]);
    }
    puts("");
  }
  return 0;
}
