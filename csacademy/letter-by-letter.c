#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef long long ll;

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
ll *pushback(ll *array, int *size, ll value) {
    ll *output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int cmpPRev(const void*pb, const void*pa)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
int cmpRev(const void *b, const void *a)
{
  return ( *(ll*)a - *(ll*)b );
}


typedef struct nodeS
{
    struct nodeS * c [26];
    ll dp ;
    int num  ;
}node;
node*newNode()
{
    node*rez=malloc(sizeof(node));
    for ( int i =0  ; i< 26 ; i ++ )
        rez->c[i] = NULL;
    rez->num = 0 ;
    rez->dp  = -1;
    return rez;
}
node*root ;
int k ;
void insert ( char* s )
{
    node * tmp = root ;
    for ( int i=0 ; i < k ; i ++ )
    {
        int num = s[i] - 'a' ;
        if ( tmp -> c[num] == NULL) 
            tmp ->c[num] = newNode();
        tmp = tmp -> c[num]; 
    }
    tmp -> num =1  ;
}
bool find ( char* s )
{
    node * tmp = root ;
    for ( int i =0 ; i < k ; i ++ )
    {
        int num = s[i] - 'a' ;
        if ( tmp -> c[num] == NULL) return 0 ;
        tmp  = tmp -> c[num] ;
    }
    return 1 ;
}
ll build ( node * tmp , int ind )
{
    if ( tmp ->dp != -1 ) return tmp ->dp ;
    if ( ind == k ) 
    {
        return tmp -> dp = 0;
    }
    ll*v=NULL;int vSz=0;
    for ( int i =0  ; i< 26 ; i ++ )
    {
        if (tmp -> c[i] != NULL ) 
            v=pushback(v,&vSz,build(tmp -> c[i] , ind + 1 ));
    }
    qsort(v, vSz, sizeof(ll), cmpRev);
    ll mx = 0 ;
    for ( int i =0 ; i < vSz ; i ++ )
    mx = max ( mx , i + 1 + v[i] ) ;
    return tmp->dp = mx ;

}
void gss ( )
{
    node * tmp = root ;
    int ans = 0 ;
    while ( ans  < k )
    {
        pair*v=NULL;int vSz=0;
        for ( int i =0 ; i < 26  ; i ++ )
        {
            if ( tmp -> c[i] )
            {
                v=pushbackP(v,&vSz,newPair(tmp -> c[i] -> dp  , i ));
            }
        }
        qsort(v, vSz, sizeof(pair), cmpPRev);
        for ( int i =0  ;i< vSz; i ++ )
        {
            char x  = 'a' + v[i].second ;
            printf("%c\n", x); fflush(stdout);
            int res ;
            scanf("%d", &res);
            if ( res )
            {
                ans ++ ;
                tmp = tmp -> c[v[i].second] ;
                break ;
            }
        }
        
    }
}
#define STR_SIZE 100000
char s[ STR_SIZE ];
int main()
{
    root = newNode();
    int n;
    scanf("%d %d", &n, &k);
    for ( int i = 0 ; i < n ; i ++ )
    {
        scanf("%s", &s);
        insert ( s );
    }
    build (root , 0  ) ;
    gss ();
}



























