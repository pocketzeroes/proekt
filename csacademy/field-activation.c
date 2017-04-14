#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


#define BUFFLEN 4000000

int*ed[BUFFLEN];int sz1[BUFFLEN];
int*ob[BUFFLEN];int sz2[BUFFLEN];
int vr1[3000][3000];
int vr2[3000][3000];
int ll,rr;
int v,n,m,q;
int lf [BUFFLEN];
int f  [BUFFLEN];
int vis[BUFFLEN];
int dl [BUFFLEN];
int cl=0,k=0,b[1000000];
int into[1000000];
int mar[1000000];
int*ord[1000000];int sz3[1000000];
int mx=0;

void buildj(int xn, int xk , int l, int r) {
    v++;
    vr1[xn][xk]=v;
    if (ll<rr || l<r) v++;
    else lf[v]=1;
    vr2[xn][xk]=v;
    if (xk!=1) {
        int index=vr1[xn][xk];
        ed[index] = pushback(ed[index], sz1+index, vr1[xn][xk/2]);
        int idx=vr2[xn][xk/2];
        ed[idx]=pushback(ed[idx], sz1+idx, vr2[xn][xk]);
    }
    if (xn!=1) {
        int id1=vr1[xn][xk];
        ed[id1] = pushback(ed[id1], sz1+id1, vr1[xn/2][xk]);
        int id2=vr2[xn/2][xk];
        ed[id2] = pushback(ed[id2], sz1+id2, vr2[xn][xk]);
    }
    if (l==r) return;
    int mid=(r+l)/2;
    buildj(xn,xk*2,l,mid);
    buildj(xn,xk*2+1,mid+1,r);
}
void build(int x, int l, int r) {
    ll=l;
    rr=r;
    buildj(x,1,1,m);
    if (l==r) return;
    int mid=(r+l)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
}
void get2(int xn, int xk, int l, int r, int ly, int ry, int tp) {
    if (ly<=l && r<=ry) {
        if (tp==0){
            int off=vr1[xn][xk];
            ed[off]=pushback(ed[off], sz1+off, v);
        }
        else{  
            ed[v] = pushback(ed[v], sz1+v, vr2[xn][xk]);
        }
        return;
    }
    int mid=(r+l)/2;
    if (ly<=mid) get2(xn,xk*2,l,mid,ly,ry,tp);
    if (ry>mid) get2(xn,xk*2+1,mid+1,r,ly,ry,tp);
}
void get(int x, int l, int r, int lx, int rx, int ly, int ry, int tp) {
     if (lx<=l && r<=rx) {
        get2(x,1,1,m,ly,ry,tp);
        return;
    }
    int mid=(r+l)/2;
    if (lx<=mid) get(x*2,l,mid,lx,rx,ly,ry,tp);
    if (rx>mid) get(x*2+1,mid+1,r,lx,rx,ly,ry,tp);
}
void dfs1(int x) {
    mar[x]=1;
    for (int i=0;i<sz1[x];i++) {
        int to=ed[x][i];
        ob[to]=pushback(ob[to], sz2+to, x);
        if (mar[to]==1) continue;
        dfs1(to);
    }
    k++;
    b[k]=x;
}
void dfs2(int x) {
    mar[x]=cl;
    for (int i=0;i<sz2[x];i++) {
        int to=ob[x][i];
        if (mar[to]!=0) continue;
        dfs2(to);
    }
}
void dfs3(int x) {
    vis[x]=1;
    int bd=0;
    for (int i=0;i<sz3[x];i++) {
        int q=ord[x][i];
        if (lf[q]==1) bd=1;
    }
    for (int i=0;i<sz3[x];i++) {
        int q=ord[x][i];
        for (int j=0;j<sz1[q];j++) {
            int to=mar[ed[q][j]];
            if (vis[to]==0) dfs3(to);
        }
    }
    k++;
    b[k]=x;
}
void solve() {
    for (int i=1;i<=v;i++)
        if (mar[i]==0) dfs1(i);
    for (int i=1;i<=v;i++) mar[i]=0;
    cl=0;
    for (int i=k;i>=1;i--) {
        int x=b[i];
        if (mar[x]!=0) continue;
        cl++;
        dfs2(x);
    }
    for (int i=1;i<=v;i++){
        int ii=mar[i];
        ord[ii]=pushback(ord[ii], sz3+ii, i);
    }
    k=0;
    dfs3(mar[vr2[1][1]]);
    int ans=0;
    for (int i=k;i>=1;i--) {
        int x=b[i];
        int bd=0;
        for (int j=0;j<sz3[x];j++) {
            int q=ord[x][j];
            if (lf[q]==1) bd=1;
        }
        int td=0;
        if (bd==1 && dl[x]==0) ans++;
        if (bd==1 || dl[x]==1) {
            td=1;
        }
        for (int j=0;j<sz3[x];j++) {
            int q=ord[x][j];
            for (int r=0;r<sz1[q];r++) {
                int to=mar[ed[q][r]];
                if (to==x) continue;
                dl[to]=max(dl[to],td);
            }
        }
    }
    printf("%d\n", ans);
    exit(0);
}
int main() {
    scanf("%d %d %d", &n, &m, &q);
    v=0;
    build(1,1,n);
    mx=v;
    for (int i=1;i<=q;i++) {
        int lx1,rx1,ly1,ry1;
        int lx2,rx2,ly2,ry2;
        scanf("%d %d %d %d", &lx1 , &ly1 , &rx1 , &ry1);
        scanf("%d %d %d %d", &lx2 , &ly2 , &rx2 , &ry2);
        lx1++; lx2++;
        rx1++; rx2++;
        ly1++; ly2++;
        ry1++; ry2++; v++;
        get(1,1,n,lx1,rx1,ly1,ry1,0);
        get(1,1,n,lx2,rx2,ly2,ry2,1);
    }
    solve();
    return 0;
}


























































