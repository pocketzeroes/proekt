#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

const int inf = -1u / 2;
enum{ N =(int) 1e5 + 10};
int l[ N ], r[ N ], n;

int cmp(const void*pa,const void*pb){
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int id1= *ptra;
    int id2= *ptrb;
    int rv = ( l[id1] == l[id2] ? r[id1] > r[id2] : l[id1] < l[id2] );
    return rv?-1:1;
}

int main(){
    scanf("%d", &n);
    for( int i = 0 ; i < n ; ++i ){
        scanf("%d %d", &l[i], &r[i]);
    }
    int idx[n];
    for(int i=0;i<n;i++)
      idx[i]=i;
    qsort(idx,n,sizeof(int),cmp);
    int ans = 0;
    for ( int i = 0, mx = -inf ; i < n ; ++i ){
        if ( r[ idx[i] ] <= mx )
            ++ans;
        else {
            if( i+1 < n && l[ idx[i+1] ] == l[ idx[i] ] && r[ idx[i+1] ] == r[ idx[i] ] )
                ++ans;
            mx = r[ idx[i] ];
        }
    }
    printf("%d\n", ans);
    return 0;
}
