#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
#define swap(a,b) { typeof(a) tmp; tmp = a; a = b; b = tmp; }

typedef struct{
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
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int limit, mid;
char s[300000], str[300000];
int sa[300000], height[300000];
int tmp[2][300000];
int c[300000];
int n;

void concat(char t[]){
    for (int i = 0; t[i] != '\0'; i++)
        s[n++] = t[i];
    s[n++] = '\n';
}
int cmpPos(const void*pa, const void*pb){
    pair*A=(pair*)pa;
    pair*B=(pair*)pb;
    if(A->first == B->first)
        return(A->second > B->second)?-1:1;
    return(A->first < B->first)?-1:1;
}
int cmpLen(const void*pa, const void*pb){
    pair*A=(pair*)pa;
    pair*B=(pair*)pb;
    if(A->second == B->second)
        return(A->first < B->first)?-1:1;
    return(A->second > B->second)?-1:1;
}
void buildSA(int m){
    int *rank = tmp[0], *sa2 = tmp[1];
    for (int i = 0; i < m; i++) c[i] = 0;
    for (int i = 0; i < n; i++) c[rank[i] = s[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; i--)    sa[--c[s[i]]] = i;
    for (int i = 1; i < n; i *= 2){
        int r = 0;
        for (int j = n - i; j < n; j++) sa2[r++] = j;
        for (int j = 0; j < n; j++)
            if (sa[j] >= i)
                sa2[r++] = sa[j] - i;
        for (int j = 0; j < m; j++) c[j] = 0;
        for (int j = 0; j < n; j++) c[rank[sa2[j]]]++;
        for (int j = 1; j < m; j++) c[j] += c[j - 1];
        for (int j = n - 1; j >= 0; j--)    sa[--c[rank[sa2[j]]]] = sa2[j];
#define newRank sa2
        newRank[sa[0]] = r = 0;
        for (int j = 1; j < n; j++){
            if (!(rank[sa[j - 1]] == rank[sa[j]] && rank[sa[j - 1] + i] == rank[sa[j] + i]))
                r++;
            newRank[sa[j]] = r;
        }
        swap(rank, sa2);
        if (r == n - 1)
            break;
        m = r + 1;
    }
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;
    for (int i = 0, k = 0; i < n - 1; i++){
        if (k)
            k--;
        int j = sa[rank[i] - 1];
        while (s[i + k] == s[j + k])
            k++;
        height[rank[i]] = k;
    }
}
void solve(){
    memset(c, 0, sizeof(c));
    for (int i = 0, k = 0; i < n; i++){
        if (sa[i] < mid)
            k = height[i + 1];
        else{
            k = min(height[i], k);
            c[i] = max(c[i], k);
        }
    }
    for (int i = n - 1, k = 0; i >= 0; i--){
        if (sa[i] < mid)
            k = height[i];
        else{
            c[i] = max(c[i], k);
            k = min(height[i], k);
        }
    }
    vecp L   = newVecP();
    vecp ans = newVecP();
    for(int i = 0; i < n; i++)
        if(c[i] >= 1)
            L.ptr = pushbackP(L.ptr, &L.sz, newPair(sa[i], c[i]));
    qsort(L.ptr, L.sz, sizeof(pair), cmpPos);
    for (int i = 0, k = -1; i < L.sz; i++){
        if(L.ptr[i].first + L.ptr[i].second <= k)
            continue;
        ans.ptr = pushbackP(ans.ptr, &ans.sz, L.ptr[i]);
        k = L.ptr[i].first + L.ptr[i].second;
    }
    qsort(ans.ptr, ans.sz, sizeof(pair), cmpLen);
    for(int i = 0; i < limit && i < ans.sz; i++){
        printf("INFRINGING SEGMENT %d LENGTH %d POSITION %d\n", i + 1, ans.ptr[i].second, ans.ptr[i].first - mid);
        for (int j = 0; j < ans.ptr[i].second; j++)
            putchar(s[ans.ptr[i].first + j]);
        printf("\n");
    }
}
int main(){
    int ca = 1;
    while (scanf("%d", &limit) == 1 && limit){
        if (ca > 1) putchar('\n');
        printf("CASE %d\n", ca++);
        gets(str);
        n = 0;
        gets(str);
        while (gets(str) && strcmp(str, "END TDP CODEBASE"))
            concat(str);
        gets(str);
        s[n++] = 1;
        mid = n;
        while (gets(str) && strcmp(str, "END JCN CODEBASE"))
            concat(str);
        s[n++] = '\0';
        buildSA(256);
        solve();
    }
    return 0;
}
