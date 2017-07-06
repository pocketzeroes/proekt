#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

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

enum{ N=100005};

vec a[N],g[N];
int ans[N],s[N];

void dfs(int cnt,int u)
{
    for(int i=0; i<g[u].sz; i++)
    {
        int x=g[u].ptr[i], y=abs(x);
        if(x>0&&s[y]==0)
          s[y]=1,cnt++;
        else if(x<0&&s[y]==1)
          s[y]=0,cnt--;
        else
          g[u].ptr[i]=-1;
    }
    ans[u]=cnt;
    for(int i=0; i<a[u].sz; i++)
      dfs(cnt, a[u].ptr[i]);
    for(int i=0; i<g[u].sz; i++)
    {
        int x=g[u].ptr[i],y=abs(x);
        if(g[u].ptr[i]==-1)
          continue;
        if(x>0&&s[y]==1)
          s[y]=0,cnt--;
        else if(x<0&&s[y]==0)
          s[y]=1,cnt++;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=1; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        a[x].ptr = pushback(a[x].ptr, &a[x].sz, i+1);
    }
    for(int i=1; i<=n; i++)
    {
        int k;
        scanf("%d", &k);
        for(int j=0;j<k;j++)
        {
            int x;
            scanf("%d", &x);
            g[i].ptr = pushback(g[i].ptr, &g[i].sz, x);
        }
    }
    dfs(0,1);
    for(int i=1;i<=n;i++)
      printf("%d\n", ans[i]);
    return 0;
}


















































