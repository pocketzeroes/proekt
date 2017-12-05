#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

typedef struct{
    int first;
    int second;
}Pair;
Pair newPair(int a, int b){
    Pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

int cmpP(Pair a, Pair b){
  int diff;
  diff = a.first  - b.first; if(diff!=0) return diff;
  return a.second - b.second;
}
void merge(Pair*arr, int size1, int size2){
    Pair temp[size1+size2];
    int ptr1=0, ptr2=0;
    while(ptr1+ptr2 < size1+size2){
        if(ptr1 < size1 && cmpP(arr[ptr1], arr[size1+ptr2])<=0 || ptr1 < size1 && ptr2 >= size2)
            temp[ptr1+ptr2] = arr[ptr1++];
        if(ptr2 < size2 && cmpP(arr[size1+ptr2], arr[ptr1])<0 || ptr2 < size2 && ptr1 >= size1)
            temp[ptr1+ptr2] = arr[size1+ptr2++];
    }
    for(int i=0; i < size1+size2; i++)
        arr[i] = temp[i];
}
void mergeSort(Pair*arr, int size){
    if(size == 1)
        return;  
    int size1 = size/2, size2 = size-size1;
    mergeSort(arr, size1);
    mergeSort(arr+size1, size2);
    merge(arr, size1, size2);
}

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

//////////////////////

enum{ SIZE = 1 << 10};
int pointer = SIZE;
char buffer[SIZE];
enum{ MAXN = 100000};
int v[1 + MAXN];
int maximum[1 + 4 * (MAXN + 2)], steps[1 + MAXN];
int Stack[1 + MAXN];
ll sum[1 + 4 * (MAXN + 2)], lazy[1 + 4 * (MAXN + 2)];
Pair vn[1 + MAXN];
vec where[1 + MAXN];
bool found;
int position;




void BuildTree(int node, int left, int right){
    if (left == right) {
        maximum[node] = v[left];
        sum[node] = steps[left];
        return;
    }
    int middle = (left + right) / 2;
    BuildTree(2 * node, left, middle);
    BuildTree(2 * node + 1, middle + 1, right);
    maximum[node] = max(maximum[2 * node], maximum[2 * node + 1]);
    sum[node] = sum[2 * node] + sum[2 * node + 1];
}
void Normalize(int n){
    for (int i = 1; i <= n; i++)
        vn[i] = newPair(v[i], i);
    mergeSort(vn+1, n);
    int number = 0;
    for (int i = 1; i <= n; i++) {
        if (vn[i].first != vn[i - 1].first)
            number++;
        v[vn[i].second] = number;
    }
}
int GetMaximum(int node, int left, int right, int from, int to){
    if (from > to)
        return 0;
    if (from <= left && right <= to)
        return maximum[node];
    int middle = (left + right) / 2, answer = 0;
    if (from <= middle)
        answer = max(answer, GetMaximum(2 * node, left, middle, from, to));
    if (middle + 1 <= to)
        answer = max(answer, GetMaximum(2 * node + 1, middle + 1, right, from, to));
    return answer;
}
void Modify(int node, int left, int right, int whereby, int change){
    if (left == right) {
        maximum[node] = change;
        return;
    }
    int middle = (left + right) / 2;
    if (whereby <= middle)
        Modify(2 * node, left, middle, whereby, change);
    else
        Modify(2 * node + 1, middle + 1, right, whereby, change);
    maximum[node] = max(maximum[2 * node], maximum[2 * node + 1]);
}
void Propagate(int node){
    lazy[2 * node]     += lazy[node];
    lazy[2 * node + 1] += lazy[node];
    lazy[node] = 0;
}
void Add(int node, int left, int right, int from, int to, int add){
    if (from > to)
        return;
    if (from <= left && right <= to) {
        lazy[node] += add;
        return;
    }
    Propagate(node);
    int middle = (left + right) / 2;
    if (from <= middle)
        Add(2 * node, left, middle, from, to, add);
    if (middle + 1 <= to)
        Add(2 * node + 1, middle + 1, right, from, to, add);
    sum[node] = sum[2 * node] + lazy[2 * node] * (middle - left + 1) + sum[2 * node + 1] + lazy[2 * node + 1] * (right - middle);
}
ll Sum(int node, int left, int right, int from, int to){
    if (from <= left && right <= to)
        return sum[node] + lazy[node] * (right - left + 1);
    Propagate(node);
    int middle = (left + right) / 2;
    ll answer = 0;
    if (from <= middle)
        answer += Sum(2 * node, left, middle, from, to);
    if (middle + 1 <= to)
        answer += Sum(2 * node + 1, middle + 1, right, from, to);
    sum[node] = sum[2 * node] + lazy[2 * node] * (middle - left + 1) + sum[2 * node + 1] + lazy[2 * node + 1] * (right - middle);

    return answer;
}
void Change(int node, int left, int right, int whereat, int change){
    if (left == right) {
        lazy[node] = 0;
        sum[node] = change;
        return;
    }
    Propagate(node);
    int middle = (left + right) / 2;
    if (whereat <= middle)
        Change(2 * node, left, middle, whereat, change);
    else
        Change(2 * node + 1, middle + 1, right, whereat, change);
    sum[node] = sum[2 * node] + lazy[2 * node] * (middle - left + 1) + sum[2 * node + 1] + lazy[2 * node + 1] * (right - middle);
}
void FindLeft(int node, int left, int right, int from, int to, int limit){
    if (from <= left && right <= to) {
        if (found || maximum[node] < limit)
            return;
        found = true;
        while (left != right) {
            int middle = (left + right) / 2;
            if (maximum[2 * node + 1] >= limit) {
                node = 2 * node + 1;
                left = middle + 1;
            }
            else {
                node = 2 * node;
                right = middle;
            }
        }
        position = left;
        return;
    }
    int middle = (left + right) / 2;
    if (middle + 1 <= to)
        FindLeft(2 * node + 1, middle + 1, right, from, to, limit);
    if (from <= middle)
        FindLeft(2 * node, left, middle, from, to, limit);
}
void FindRight(int node, int left, int right, int from, int to, int limit){
    if (from <= left && right <= to) {
        if (found || maximum[node] < limit)
            return;
        found = true;
        while (left != right) {
            int middle = (left + right) / 2;
            if (maximum[2 * node] >= limit) {
                node = 2 * node;
                right = middle;
            }
            else {
                node = 2 * node + 1;
                left = middle + 1;
            }
        }
        position = left;
        return;
    }
    int middle = (left + right) / 2;
    if (from <= middle)
        FindRight(2 * node, left, middle, from, to, limit);
    if (middle + 1 <= to)
        FindRight(2 * node + 1, middle + 1, right, from, to, limit);
}
void Initialize(int n){
    v[0] = v[n + 1] = n + 1;
    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && v[i] >= v[Stack[top]])
            top--;
        steps[i] += top;
        top++;
        Stack[top] = i;
        int idx=v[i];
        where[idx].ptr = pushback(where[idx].ptr, &where[idx].sz, i);
    }
    top = 0;
    for (int i = n; i >= 1; i--) {
        while (top && v[i] >= v[Stack[top]])
            top--;
        steps[i] += top;
        top++;
        Stack[top] = i;
    }
    BuildTree(1, 0, n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < where[i].sz; j++) {
            int a = where[i].ptr[j - 1], b = where[i].ptr[j];
            if (GetMaximum(1, 0, n + 1, a + 1, b - 1) < i)
                Add(1, 0, n + 1, a + 1, b - 1, -1);
        }
}
void Update(int n, int x){
    if (v[x] == v[x + 1])
        return;
    int small = min(v[x], v[x + 1]), big = max(v[x], v[x + 1]), y, z;
    found = false;
    FindLeft(1, 0, n + 1, 0, x - 1, small);
    y = position;
    found = false;
    FindRight(1, 0, n + 1, x + 2, n + 1, small);
    z = position;
    if (v[y] != small) {
        int add = 1;
        if (v[x] == small)
            add = -1;
        Add(1, 0, n + 1, y + 1, x - 1, add);
    }
    if (v[z] != small) {
        int add = -1;
        if (v[x] == small)
            add = 1;
        Add(1, 0, n + 1, x + 2, z - 1, add);
    }
    swap(v, x, x+1);
    Modify(1, 0, n + 1, x, v[x]);
    Modify(1, 0, n + 1, x + 1, v[x + 1]);
    if (v[x] == big) {
        int a = Sum(1, 0, n + 1, x + 1, x + 1), b = Sum(1, 0, n + 1, z, z);
        Change(1, 0, n + 1, x, a);
        if (v[z] == small)
            Change(1, 0, n + 1, x + 1, b);
        else
            if (v[z] < big)
                Change(1, 0, n + 1, x + 1, b + 1);
            else
                Change(1, 0, n + 1, x + 1, a + 1);
    }
    else {
        int a = Sum(1, 0, n + 1, x, x), b = Sum(1, 0, n + 1, y, y);
        Change(1, 0, n + 1, x + 1, a);
        if (v[y] == small)
            Change(1, 0, n + 1, x, b);
        else
            if (v[y] < big)
                Change(1, 0, n + 1, x, b + 1);
            else
                Change(1, 0, n + 1, x, a + 1);
    }
}
int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    Normalize(n);
    Initialize(n);
    int type;
    while (scanf("%d", &type) == 1)
        if (type == 2){
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%lld\n", Sum(1, 0, n + 1, a, b) * k + 1LL * (n - 1) * (b - a + 1));
        }
        else{
            int x;
            scanf("%d", &x);
            Update(n, x);
        }
    return 0;
}





