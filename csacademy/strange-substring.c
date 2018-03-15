#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}


enum{ N=(int)2e5+7};
int a[N][26],l[N],r[N],fa[N],p,q,np,nq,last=1,i,sz=1,c,n,m,t[N],b[N],tmp;char s[N];long long ans;

void add(int c){
	p=last;np=last=++sz;l[np]=l[p]+1;
	while(p&&!a[p][c])a[p][c]=np,p=fa[p];
	if(!p)fa[np]=1;
	else{
		q=a[p][c];
		if(l[p]+1==l[q])fa[np]=q;
		else{
			nq=++sz;l[nq]=l[p]+1;
			memcpy(a[nq],a[q],sizeof(a[q]));
			fa[nq]=fa[q];
			fa[np]=fa[q]=nq;
			while(a[p][c]==q)a[p][c]=nq,p=fa[p];
		}
	}
}
int main(){
	for(scanf("%s",s+1),n=strlen(s+1),i=1;i<=n;++i)add(s[i]-'a');
	for(scanf("%s",s+1),m=strlen(s+1),p=1,tmp=0,i=1;i<=m;++i){
		c=s[i]-'a';
		if(a[p][c])tmp++,p=a[p][c];
		else{
			while(p&&!a[p][c])p=fa[p];
			if(!p)p=1,tmp=0;
			else tmp=l[p]+1,p=a[p][c];
		}
		r[p]=max(r[p],tmp);
	}
	for(i=1;i<=sz;++i)b[l[i]]++;
	for(i=1;i<=n;++i)b[i]+=b[i-1];
	for(i=sz;i;--i)t[b[l[i]]--]=i;
	for(i=sz;i;--i)if(r[t[i]])r[fa[t[i]]]=max(r[fa[t[i]]],l[fa[t[i]]]);
	for(i=2;i<=sz;++i)ans+=(l[i]-max(l[fa[i]],r[i]));
	return 0*printf("%lld\n",ans);
}