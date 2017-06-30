#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

char s[1000];

int main()
{
    ll x=0;
    scanf("%s", &s);
    int fl=0,tot=0;
    int ssize=strlen(s);
    for(int i=0; s[i]; i++)
    {
        if((s[i]-'0')%2==0)
            fl=1,tot++;
        x=x*10+(s[i]-'0');
    }
    ll tmp;
    tmp=x;
    if(fl==0)
    {
        puts("-1");
        return 0;
    }
    int cnt=0,pos=-1;
    for(int i = ssize-1; i>=0; i--)
    {
        if((s[i]-'0')%2==0)
        {
            pos=i;
            break;
        }
        cnt++;
    }
    int tpos=pos;
    x=0LL;
    if(s[pos]!='0')
    {
        for(int i=0;i<pos;i++)
        {
            x=x*10+(s[i]-'0');
        }
        x=x*10+((s[pos]-'0')-1);
        for(int i=pos+1;i<ssize;i++)
            x=x*10+9;
    }
    else{
        ll num=0;
        x=0;
        for(int pp=0;pp<ssize;pp++)
        {
            num=num*10;
            for(int dg=0;dg<s[pp]-'0';dg++)
            {
                ll tt=num+dg;
                for(int j=pp+1;j<ssize;j++)
                {
                    tt*=10;
                    tt+=9;
                }
                char*t_s=NULL;
                asprintf(&t_s, "%ld", tt);
                int pt=0;
                for(int i=0;t_s[i]; i++)
                {
                    if( (t_s[i]-'0')%2==0)
                        pt++;
                }
                if(pt<tot)
                    x=max(x,tt);
            }
            num+=s[pp]-'0';
        }
    }
    ll a=tmp-x;
    x=0;
    pos=tpos;
    for(int i=0;i<pos;i++)
        x=x*10+(s[i]-'0');
    x=x*10+((s[pos]-'0')+1);
    for(int i=pos+1;i<ssize; i++)
        x=x*10+1;
    ll b=x-tmp;
    ll ans=a*b;
    printf("%lld",ans), puts("");
    return 0;
}



















































