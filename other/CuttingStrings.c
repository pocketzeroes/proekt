#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ oo = 1000000000};

int*suffixArray(char*str){
    int n = strlen(str);
    int order[n];
    for(int i=0; i<n; i++)
        order[i] = n-i-1;
int lmb(const void*pa, const void*pb){
    int*aa = (int*)pa;
    int*bb = (int*)pb;
    int a = *aa;
    int b = *bb;
    return str[a] - str[b];
}
    qsort(order, n, sizeof(int), lmb);
    int*sa = calloc(n, sizeof(int));
    int classes[n];
    for(int i=0; i<n; i++){
        sa[i] = order[i];
        classes[i] = str[i];
    }
    for (int len = 1; len < n; len *= 2){
        int c[n]; memcpy(c, classes, sizeof(c));
        for (int i = 0; i < n; i++)
            classes[sa[i]] = i > 0 && c[sa[i - 1]] == c[sa[i]] && sa[i - 1] + len < n && c[sa[i - 1] + len / 2] == c[sa[i] + len / 2] ? classes[sa[i - 1]] : i;
        int cnt[n];
        for(int i=0; i<n; i++)
            cnt[i] = i;
        int s[n]; memcpy(s, sa, sizeof(s));
        for(int i = 0; i < n; i++){
            int s1 = s[i] - len;
            if (s1 >= 0)
                sa[cnt[classes[s1]]++] = s1;
        }
    }
    return sa;
}
int main(){
    int t = in_nextInt();
    while(t-->0) {
        int k = in_nextInt();
        char*str = getstr();
        int n = strlen(str);
        int*suf = suffixArray(str);
        int rev[n];
        for (int i = 0; i < n; i++)
            rev[suf[i]] = i;
        int nexts [n+1][26];
        int counts[n+1];
        fill(nexts[n], 26, oo);
        for(int i = n - 1; i >= 0; i--){
            for(int j = 0; j < 26; j++)
                nexts[i][j] = nexts[i + 1][j];
            nexts[i][str[i] - 'a'] = i;
            counts[i] = 1 + (i < n - 1 && str[i] == str[i + 1] ? counts[i + 1] : 0);
        }
        int idx = 0;
        for(int ch = 25; ch >= 0 && idx < n && k > 0; ch--){
            char let = (char) (ch + 'a');
            while(idx < n && str[idx] == let)
                putchar(str[idx++]);
            vec list = newVec();
            for(int i = idx + 1; i < n && nexts[i][ch] < oo; i++){
                if (str[i] == let && str[i - 1] != let)
                    list.ptr = pushback(list.ptr, &list.sz, i);
            }
            if(list.sz==0)
                continue;
int cmp(const void*pa, const void*pb){
    int*aa = (int*)pa;
    int*bb = (int*)pb;
    int a = *aa;
    int b = *bb;
    return counts[a] == counts[b] ? a - b : counts[b] - counts[a];
}
            qsort(list.ptr, list.sz, sizeof(int), cmp);
            int i, last = 0;
            for (i = 0; i < list.sz && k-- > 0; i++){
                int j = list.ptr[i];
                last = j;
                while(j < n && str[j] == let)
                    putchar(str[j++]);
                idx = fmax(idx, j);
            }
            int best = idx - 1;
            for(int j = i; j < list.sz; j++){
                int jj = list.ptr[j];
                if(jj > idx && counts[jj] == counts[last] && rev[jj + counts[jj] - 1] > rev[best])
                    best = jj + counts[jj] - 1;
            }
            idx = best + 1;
        }
        for(int i = idx; i < n; i++)
            putchar(str[i]);
        puts("");
    }
    return 0;
}
