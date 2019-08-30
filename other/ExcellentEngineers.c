#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ mod = 1000000007};
int n,t;

typedef struct{
    int x,y,z;
}node;
node a[100005];
int s[100005<<2];

int cmp(const void*pa, const void*pb){
    node*a=(node*)pa;
    node*b=(node*)pb;
    return(a->x < b->x)?-1:1;
}
void pushup(int i){
    s[i] = fmin(s[2*i],s[2*i+1]);
}
void updata(int l,int r,int i,int pos,int val){
    if(l == r){
        s[i] = val;
        return;
    }
    int mid = (l+r)/2;
    if(pos<=mid)
        updata(l,mid,2*i,pos,val);
    else
        updata(mid+1,r,2*i+1,pos,val);
    pushup(i);
}
int query(int L,int R,int l,int r,int i){
    if(L<=l&&r<=R)
        return s[i];
    int mid = (l+r)/2,minn = 0x3f3f3f3f;
    if(L<=mid)
        minn = fmin(minn,query(L,R,l,mid,2*i));
    if(R>=mid+1)
        minn = fmin(minn,query(L,R,mid+1,r,2*i+1));
    return minn;
}
int main(){
    scanf("%d",&t);
    while(t--){
        memset(s,0x3f3f3f3f,sizeof(s));
        int i;
        scanf("%d",&n);
        for(i = 0; i<n; i++)
            scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
        qsort(a, n, sizeof(node), cmp);
        int ans = 0;
        for(i = 0; i<n; i++){
            if(a[i].y!=1){
                int tem = query(1,a[i].y-1,1,n,1);
                if(tem<a[i].z)
                    continue;
            }
            ans++;
            updata(1,n,1,a[i].y,a[i].z);
        }
        printf("%d\n",ans);
    }
    return 0;
}
