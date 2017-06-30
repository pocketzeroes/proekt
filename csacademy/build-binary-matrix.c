#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
int unique(int *a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}


enum{ MAXH=1000};
enum{ MAXW=1000};
int h,w;
int rg[MAXH];
int cg[MAXW];
int rid[MAXH],nrid;
int cid[MAXW],ncid;
int A[MAXH][MAXW];
char ret[MAXH][MAXW+1];

bool gen(int h,int w) {
    memset(A,0,sizeof(A));
    if(h>=w) {
        int nbit=1; while((1<<nbit)<h) ++nbit; if(nbit>w) return false;
        for(int i=0;i<w;++i) A[i][i]=1;
        int at=w;
        for(int i=0;i<h;++i) if(at<h) if(i==0||(i&-i)!=i) {
            for(int j=0;j<nbit;++j) if(i&(1<<j)) A[at][j]=1;
            ++at;
        }
    }
    else {
        int nbit=1; while((1<<nbit)<w) ++nbit; if(nbit>h) return false;
        for(int i=0;i<h;++i) A[i][i]=1;
        int at=h;
        for(int i=0;i<w;++i) if(at<w) if(i==0||(i&-i)!=i) {
            for(int j=0;j<nbit;++j) if(i&(1<<j)) A[j][at]=1;
            ++at;
        }
    }
    return true;
}

int main() {
    scanf("%d%d",&h,&w);
    for(int i=0;i<h;++i) 
        scanf("%d",&rg[i]);
    for(int i=0;i<w;++i) 
        scanf("%d",&cg[i]);
    nrid=0; 
    for(int i=0;i<h;++i) 
        rid[nrid++]=rg[i]; 
    qsort(rid, nrid, sizeof(int), cmp);
    nrid=unique(rid, nrid);
    ncid=0; 
    for(int i=0;i<w;++i) 
        cid[ncid++]=cg[i]; 
    qsort(cid, ncid, sizeof(int), cmp);
    ncid=unique(cid, ncid);
    for(int i=0;i<h;++i) 
        rg[i] = lower_bound(rid, nrid, rg[i]);
    for(int i=0;i<w;++i) 
        cg[i] = lower_bound(cid, ncid, cg[i]);
    if(!gen(nrid,ncid)) { 
        printf("-1\n"); 
        return 0;
    }
    for(int i=0;i<h;++i) 
        for(int j=0;j<w;++j) 
            ret[i][j]='0'+A[rg[i]][cg[j]]; 
    for(int i=0;i<h;++i) 
        ret[i][w]='\0'; 
    for(int i=0;i<h;++i) 
        printf("%s\n",ret[i]);
}




























































