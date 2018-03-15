#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

inline int read(){
    int x=0,f=1; char ch=getchar();
    while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}
enum{ MAXN = 300005,
      Mo = 1000000007};
int n,m,q,a[MAXN],b[MAXN],ch[MAXN][2];

void dfs(int x,int y){
    if (!x) 
        return;
    dfs(ch[x][0],y+1); 
    dfs(ch[x][1],y+1);
    b[x]=(b[ch[x][0]]^y)*(b[ch[x][1]]^y)%Mo;
}
int main(){
    int T=read();
    while (T--) {
        n=read();
        for (int i=(1);i<=(n);++i) 
            a[i]=read(),ch[i][0]=ch[i][1]=0;
        b[0]=0;
        for (int i=(1);i<=(n);++i)
        if (a[i])
            if (ch[a[i]][0]) 
                ch[a[i]][1]=i; 
            else 
                ch[a[i]][0]=i;
        else 
            m=i;
        dfs(m,1); 
        q=b[m];
        for (int i=(1);i<=(n);++i) 
            a[i]=read(),ch[i][0]=ch[i][1]=0; b[0]=0;
        for (int i=(1);i<=(n);++i)
        if (a[i])
            if (ch[a[i]][0]) 
                ch[a[i]][1]=i; 
            else 
                ch[a[i]][0]=i;
        else 
            m=i;
        dfs(m,1);
        printf("%d\n",q==b[m]);
    }
    return 0;
}



