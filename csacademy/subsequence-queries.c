#include <stdio.h>
#include <string.h>


enum{ sigma=(int) 9      };
enum{ mod  =(int) (1e9)+7};

struct arbint
{
    int cnt[sigma][sigma],v[sigma];
}arb[120000];
int aux[sigma],sol[sigma];
char sir[30010];

void arbint_init(int nod,int st,int dr)
{
    for(int i=0;i<sigma;i++) arb[nod].cnt[i][i]=1;
    for(int i=st;i<=dr;i++)
    {
        int s=1;
        for(int j=0;j<sigma;j++) aux[j]=0;
        for(int j=0;j<sigma;j++)
            for(int k=0;k<sigma;k++) aux[k]=(aux[k]+arb[nod].cnt[j][k])%mod;
        for(int j=0;j<sigma;j++)
            s=(s+arb[nod].v[j])%mod;
        for(int j=0;j<sigma;j++)
            arb[nod].cnt[sir[i]-'a'][j]=aux[j];
        arb[nod].v[sir[i]-'a']=s;
    }
    if(st==dr) return;
    int mid=(st+dr)/2;
    arbint_init(nod*2,st,mid);
    arbint_init(nod*2+1,mid+1,dr);
}

void arbint_query(int nod,int st,int dr,int left,int right)
{
    if(left<=st && dr<=right)
    {
        for(int i=0;i<sigma;i++)
        {
            aux[i]=arb[nod].v[i];
            for(int j=0;j<sigma;j++)
                aux[i]=(aux[i]+1LL*sol[j]*arb[nod].cnt[i][j])%mod;
        }
        for(int i=0;i<sigma;i++) sol[i]=aux[i];
    }
    else
    {
        int mid=(st+dr)/2;
        if(left<=mid) arbint_query(nod*2,st,mid,left,right);
        if(mid<right) arbint_query(nod*2+1,mid+1,dr,left,right);
    }
}

int main()
{
    scanf("%s",sir+1);
    int n=strlen(sir+1),q;
    arbint_init(1,1,n);
    for(scanf("%d",&q);q;q--)
    {
        int x,y,s=0;
        scanf("%d%d",&x,&y);
        for(int i=0;i<sigma;i++) sol[i]=0;
        arbint_query(1,1,n,x,y);
        for(int i=0;i<sigma;i++) s=(s+sol[i])%mod;
        printf("%d\n",s);
    }
    return 0;
}



