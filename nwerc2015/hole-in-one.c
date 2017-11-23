#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

void swap(int*nums, int i, int j) {
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

//////////////////////
int N, coords[15][4], dup[15][4], hole[2], dupHole[2], orig[2], best = -1;
vec perms;
vec lastPerms;
double g[3], h[3];


int ccw(int* a, int *b, int *p){
    int c = (b[0] - a[0]) * (p[1] - a[1]) - (p[0] - a[0]) * (b[1] - a[1]);
    return (c == 0 ? 0 : (c > 0) ? 1 : -1);
}
inline bool intersects(int*S, int*T, int*A, int*B){
  return(ccw(A,B,S) * ccw(A,B,T) <= 0);
}
void getLine(int *p0, int *p1, double *l){
    l[0] = p1[1]-p0[1], l[1] = p0[0]-p1[0];
    l[2] = l[0]*p0[0] + l[1]*p0[1];
}
void flip(int wall, int *data){
    if(dup[wall][0] == dup[wall][2])
        data[0] = 2*dup[wall][0] - data[0];
    else
        data[1] = 2*dup[wall][1] - data[1];
}
double getDist(int wall){
    if (intersects(orig, dupHole, dup[wall], dup[wall] + 2) &&
        intersects(dup[wall], dup[wall] + 2, orig, dupHole)){
        getLine(orig, dupHole, g);
        getLine(dup[wall], dup[wall] + 2, h);
        double det = g[0]*h[1] - h[0]*g[1], sx = g[2]*h[1] - h[2]*g[1], sy = g[0]*h[2] - h[0]*g[2];
        return sqrt(sx*sx + sy*sy) / abs(det);
    }
    else
        return -1;
}
void flippy(int allowed){
    for (int i=(0); i<(2); i++)
        dupHole[i] = hole[i];
    for (int i=(0); i<(N); i++)
        for (int j=(0); j<(4); j++)
            dup[i][j] = coords[perms.ptr[i]][j];
    for (int i=(0); i<(allowed); i++){
        flip(i, dupHole);
        for (int j=(i+1); j<(N); j++)
            for (int k=(0); k<(2); k++)
                flip(i, dup[j] + 2*k);
    }
    for (int i=(0); i<(N); i++)
        for (int j=(0); j<(4); j++)
            dup[i][j] = coords[perms.ptr[i]][j];
    double lastDist = 0, distHole = sqrt(dupHole[0]*dupHole[0] + dupHole[1]*dupHole[1]);
    for (int i=(0); i<(allowed+1); i++) {
        double flipDist = (i == allowed) ? distHole : getDist(i);
        if (flipDist < 0)
            return;
        for (int j=(0); j<(N); j++) {
            if (i == j && i != allowed)
                continue;
            double lineDist = getDist(j);
            if (lineDist >= 0 && lastDist < lineDist && lineDist < flipDist)
                return;
        }
        lastDist = flipDist;
        for (int j=(i+1); j<(N); j++)
            for (int k=(0); k<(2); k++)
                flip(i, dup[j] + 2*k);
    }
    best = max(best, allowed);
}
int main(){
    scanf("%d %d %d", &N, &hole[0], &hole[1]);
    for(int i=(0); i<(N); i++)
        for (int j=(0); j<(4); j++)
            scanf("%d", &coords[i][j]);
    for(int i=(0); i<(N); i++)
        perms.ptr = pushback(perms.ptr, &perms.sz, i);
    for(int i=(0); i<(N); i++)
        lastPerms.ptr = pushback(lastPerms.ptr, &lastPerms.sz, -1);
    flippy(0);
    do{
        int firstDiff = N;
        for(int i=(0); i<(N); i++)
            if(lastPerms.ptr[N-1-i] != perms.ptr[N-1-i]){
                firstDiff = N-1-i;
                lastPerms.ptr[N-1-i] = perms.ptr[N-1-i];
            }
        for(int i=(firstDiff); i<(N); i++)
            flippy(i+1);
    }
    while(next_permutation(perms.ptr, perms.sz));
    if(best < 0)
        puts("impossible");
    else
        printf("%d\n", best);
    return 0;
}
