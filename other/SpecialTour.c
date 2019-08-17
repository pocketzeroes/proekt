#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
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
typedef long long ll;

enum{ MAXN = 100000};
vec e[MAXN];
int n,m;
bool fl=0,vis[MAXN];




inline int read(){
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
void add(int a1,int b1,int a2,int b2) {
    int u=(((a1)-1)*m+(b1));
    int v=(((a2)-1)*m+(b2));
    e[u].ptr = pushback(e[u].ptr, &e[u].sz, v);
    e[v].ptr = pushback(e[v].ptr, &e[v].sz, u);
}
void pr(int x,int y){
    if (fl) printf("%d %d\n",y,x);
    else printf("%d %d\n",x,y);
}
void dfs(int x) {
    vis[x]=1;
    pr((x-1)/m+1,(x-1)%m+1);
    for(int z=0;z<e[x].sz;z++){int v=e[x].ptr[z];
        if (!vis[v])
            dfs(v);
    }
}
void DaBiao(){
  if (n==3 && m==3) printf("1 1\n2 2\n3 3\n2 1\n1 2\n3 1\n2 3\n3 2\n1 3\n");
  if (n==3 && m==5) printf("1 1\n2 2\n3 3\n2 4\n3 5\n1 4\n2 5\n3 4\n1 5\n2 3\n3 2\n1 3\n2 1\n1 2\n3 1\n");
  if (n==5 && m==3) printf("1 1\n2 2\n3 3\n4 2\n5 3\n4 1\n5 2\n4 3\n5 1\n3 2\n2 3\n3 1\n1 2\n2 1\n1 3\n");
  if (n==5 && m==5) printf("1 1\n2 2\n3 3\n4 4\n5 5\n4 3\n5 4\n4 5\n5 3\n4 2\n5 1\n3 2\n4 1\n5 2\n3 1\n2 3\n3 5\n1 4\n2 5\n3 4\n1 5\n2 4\n1 2\n2 1\n1 3\n");
  exit(0);
}
void work(){
    dfs(1);exit(0);
}
int main(){
    fl=0;
    scanf("%d %d", &n, &m);
    if ((n==3||n==5) &&(m==3||m==5) )
        DaBiao();
    if (n>m){
        swap(n,m);
        fl^=1;
    }
    if (n==1) {
        if(m!=5&&m<10) {
            puts("-1");
            return 0;
        }
        add(1,1,1,3);
        add(1,1,1,4);
        add(1,2,1,4);
        add(1,2,1,5);
        if (m==5) {
            add(1,3,1,5);
        }
        else {
            add(1,3,1,6);
            for(int i=7;i<=m-4;i++) {
                add(1,i-2,1,i);
            }
            add(1,m,1,m-2);
            add(1,m,1,m-3);
            add(1,m-1,1,m-3);
            add(1,m-1,1,m-4);
            add(1,m-2,1,m-5);
        }
    }
    else if (n==2 ) {
        if (m==2) {
            puts("-1");
            return 0;
        }
        add(1,1,2,2);
        add(1,2,2,1);
        add(1,1,2,3);
        add(2,1,1,3);
        for(int i=4;i<=m;i++) for(int j=1;j<=2;j++) add(j,i,j,i-2);
        add(1,m,2,m-1);
        add(2,m,1,m-1);
    }
    else if (n==4 || m==4 ) {
        if (n!=4){
            swap(n,m);
            fl^=1;
        }
        for(int t=0;t<=2;t+=2) {
            add(t+1,1,t+2,2);add(t+1,2,t+2,1);add(t+1,1,t+2,3);add(t+2,1,t+1,3);
            for(int i=4;i<=m;i++) for(int j=1;j<=2;j++) add(t+j,i,t+j,i-2);
        }
        add(1,m-1,3,m);add(2,m,4,m-1);add(1,m,2,m-1),add(3,m-1,4,m);
    }
    else {
        for(int k=1;k<=n;k++) {
            add(k,1,k,3);add(k,1,k,4);
            add(k,2,k,4);add(k,2,k,5);
            add(k,3,k,6);
            for(int i=7;i<=m;i++) add(k,i,k,i-2);
        }
        for(int i=1;i<=n-2;i++) {
            if (i&1) {
                add(i,m-1,i+2,m);
            }
            else {
                add(i,m,i+2,m-1);
            }
        }
        add(1,m,2,m-1);
        if (n&1) {
            add(n,m-1,n-1,m);
        }
        else
            add(n,m,n-1,m-1);
    }
    work();
    return 0;
}
