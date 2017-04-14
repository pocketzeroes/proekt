#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct tripS
{
    int x, y, z;
}trip;
trip newTrip(int _x, int _y, int _z)
{
    trip rez;
    rez.x=_x;
    rez.y=_y;
    rez.z=_z;
    return rez;
}
int cmpT(const void*pa, const void*pb)
{
    trip*a=(trip*)pa;
    trip*b=(trip*)pb;
    return a->y < b->y;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

trip*pushback(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}


enum{ Nmax =(int) 1e5+5};
int N, M, D, K, i, j, p, Q, x, y, l, r, n, last_col;
bool ans [Nmax];
trip*v   [Nmax];
int sizes[Nmax];
trip door[Nmax];
bool ok;


bool intersect(int argl, int argr, int argx, int argy)
{
    int c0l = last_col - argy;
    return (ok && argl-c0l<=argx && argx<=argr+c0l);
}
void intersection(int*l, int*r, int id, int t)
{
    int p = door[id].x, N = n+1, col = last_col - door[id].y, nr;
    char z = door[id].z;
    while(t)
    {
        if(z=='-')
        {
            nr = min(p-1, t);
            t -= nr;
            p -=nr;
            if(p==1) z = '+';
        }
        else
        {
            nr = min(N-p, t);
            t -= nr;
            p += nr;
            if(p==N) z = '-';
        }
    }
    last_col = door[id].y;
   *l = max((*l)-col, p);
   *r = min((*r)+col, p+D-1);
    if(*l>*r)
        ok = 0;
}
void printarr(trip*arr,int sz){
    for( int i=0;i<sz;i++)
        printf("(%d %d %d) ; ", arr[i].x, arr[i].y, arr[i].z);
    printf("\n");
}
int main()
{
    scanf("%d%d%d%d", &N, &M, &D, &K);
    n = N-D;
    for(i=1; i<=K; ++i) 
        scanf("%d %d %c\n", &door[i].x, &door[i].y, &door[i].z);
    qsort(door+1, K, sizeof(trip),cmpT);
//  printarr(door+1,K);
    scanf("%d", &Q);
//  printf("Q=%d\n", Q);
    for(i=1; i<=Q; ++i)
    {
        scanf("%d%d", &x, &y);
//      printf("x=%d y=%d\n", x, y);
        int index= n ? (M-y) % (2*n) : 0;
//      printf("index=%d\n", index);
        v[index]=pushback(v[index], sizes+index, newTrip(x,y,i));
        
    }
    for(i=0; i<=max(1, 2*n); ++i)
      if(sizes[i]>0)
      {
//        puts("before sort");printarr(v[i],sizes[i]);
        qsort(v[i], sizes[i], sizeof(trip), cmpT);
//        puts("after  sort");printarr(v[i],sizes[i]);
        p  = 0; 
        ok = 1;
        l=1, r=N; 
        last_col = M;
        for(j=1; j<=K; ++j)
        {
            while(p<sizes[i] && v[i][p].y > door[j].y)
            {
                int var=intersect(l, r, v[i][p].x, v[i][p].y);
                ans[v[i][p].z] = var;
                ++p;
//              printf("var=%d\n", var);
            }
            intersection( &l, &r, j, n ? (i - M%(2*n) + door[j].y + 2*n) % (2*n) : 0 );
        }
        for(; p<sizes[i]; ++p){
            int val = intersect(l, r, v[i][p].x, v[i][p].y);
            ans[v[i][p].z] = val;
//          printf("val=%d\n", val);
        }
      }
    for(i=1; i<=Q; ++i) 
        printf("%d\n", ans[i]);
    return 0;
}





































































