#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 1000
int X[MAXN],Y[MAXN],I[MAXN],U[MAXN],S[MAXN],sc;
double A[MAXN],sx,sy,zx,zy,z;
int k,n,i,j,a,b,pb,c,ov,zz,rr,rem;

int comp(const void *a,const void *b) {
    int k,l;
    k=*(int *) a; l=*(int *) b;
    if (A[k]<A[l]) return -1;
    if (A[k]>A[l]) return +1;
    return 0;
}
int main(){
        sc=0;
        scanf("%d",&n);
        sx=0; sy=0;
        for (j=0;j<n;j++) {
            scanf("%d %d",X+j,Y+j);
            sx+=X[j]; sy+=Y[j];
        }
        sx=sx/n; sy=sy/n;
        for (j=0;j<n;j++) {
            zx=X[j]-sx; zy=Y[j]-sy;
            z=sqrt(zx*zx + zy*zy);
            zx=zx/z; zy=zy/z;
            if (zy>=0) A[j]=1-zx; else A[j]=3+zx;
            I[j]=j;
        }
        qsort(I,n,sizeof(int),comp);
        ov=0;
        for (j=0;j<n;j++) U[j]=0;
        j=0;
        ov=0;
        while (1){
          a=(j+1)%n;
          b=(a+1)%n;
          c=2;
          while ((X[I[a]]-X[I[j]])*(Y[I[b]]-Y[I[j]]) == (Y[I[a]]-Y[I[j]])*(X[I[b]]-X[I[j]])) {
            b=(b+1)%n;
            c++;
          }
          b=(b+n-1)%n;
          if (U[b]) {
            S[sc++]=c;
            break;
          }
          U[b]=1;
          if (ov==0) ov=1; else {
            S[sc++]=c;
          }
          j=b;
        }
        rem=n;
        c=0;
        for (j=0;j<sc;j++) {
            if (S[j]>3) {
              rem-=S[j];
              S[j]=0;
              a=(j+sc-1)%sc;
              b=(j+1)%sc;
              if (S[a]) S[a]--;
              if (S[b]) S[b]--;
              c++;
            }
        }
        j=0;
        while (S[j]==3) {
              j++;
              if (j==sc) { j=0; break; }
        }
        for (zz=0;zz<sc;zz++) {
            rr=(zz+j)%sc;
            if (S[rr]==3) {
              rem-=S[rr];
              S[rr]=0;
              a=(rr+sc-1)%sc;
              b=(rr+1)%sc;
              if (S[a]) S[a]--;
              if (S[b]) S[b]--;
              c++;
            }
        }
        printf("%d\n",c+(rem+1)/2);
    return 0;
}
