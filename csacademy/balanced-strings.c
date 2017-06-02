#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdint.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int P;
enum{ N=216};
typedef struct matS{
	int a[N][N];
}mat;


void clear(mat*m, int y) {
  for(int i=0;i<y;i++) 
    for(int j=0;j<y;j++) 
      m->a[i][j]=0;
}
int ans(mat*m, int y) {
  ll z=0;
  for(int i=0;i<y;i++) 
    for(int j=0;j<y;j++) 
      z += m->a[i][j];
  return (int)(z % P);
}
mat mul( mat*A, mat*B,int y) {
	mat Z;
	for(int i=0;i<y;i++) for(int j=0;j<y;j++) {
		ll z=0;
		for(int k=0;k<y;k++) z+=1LL*A->a[i][k]*B->a[k][j];
		Z.a[i][j]=(int)(z%P);
	}
	return Z;
}
mat do_exp( mat*A, int e,int y) {
	assert(e);
	if(e==1) return *A;
	if(e&1){mat de=do_exp(A, e-1, y); return mul(A, &de, y);}
	mat B = do_exp(A, e>>1, y);
	return mul(&B, &B, y);
}
int F(int n,int _a,int _b,int _c) {
	++_a,++_b,++_c;
	int y=_a*_b*_c;
	mat A; 
  clear(&A, y);
	for(int a=0;a<_a;a++) for(int b=0;b<_b;b++) for(int c=0;c<_c;c++) {
		int I=a*_b*_c + b*_c + c;
		do {
			int aa=a+1,bb=b-1,cc=c;
			if(aa==_a || bb<0) break;
			int J=aa*_b*_c + bb*_c + cc;
			A.a[I][J]++;
		} while(0);
		do {
			int aa=a,bb=b+1,cc=c-1;
			if(bb==_b || cc<0) break;
			int J=aa*_b*_c + bb*_c + cc;
			A.a[I][J]++;
		} while(0);
		do {
			int aa=a-1,bb=b,cc=c+1;
			if(cc==_c || aa<0) break;
			int J=aa*_b*_c + bb*_c + cc;
			A.a[I][J]++;
		} while(0);
	}
  mat ee = do_exp(&A,n,y);
	return ans(&ee, y);
}
int32_t main() {
	int n,k; 
  scanf("%d %d %d",&n,&k,&P);
	ll Z=0;
	for(int a=k-1;a<=k;a++) for(int b=k-1;b<=k;b++) for(int c=k-1;c<=k;c++) {
		bool flip=(a^b^c^k^k^k)&1;
		if(flip) Z-=F(n,a,b,c);
		else Z+=F(n,a,b,c);
	}
	Z%=P;
	if(Z<0) Z+=P;
	printf("%lld\n",Z);
}








































