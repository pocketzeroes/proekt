#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef signed long long ll;

#undef _P
#define _P(...) (void)printf(__VA_ARGS__)
#define FOR(x,to) for(x=0;x<(to);x++)
#define FORR(x,arr) for(auto& x:arr)
#define ITR(x,c) for(__typeof(c.begin()) x=c.begin();x!=c.end();x++)
#define ALL(a) (a.begin()),(a.end())
#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))

int X1,Y1,X2,Y2;

void solve() {
	int i,j,k,l,r,x,y; 
	scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
	if((X1+Y1)%2!=(X2+Y2)%2) return _P("-1\n");
	if(abs(X2-X1)==0 && abs(Y2-Y1)==0) return _P("0\n");
	if(abs(X2-X1)==abs(Y2-Y1)) return _P("1\n");
	_P("2\n");
}

int main(int argc,char** argv){
	solve(); 
    return 0;
}
