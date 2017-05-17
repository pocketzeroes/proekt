#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


int allsum1[27],allsum2[27];
int a[1000100];

int getmx(int start, int end)
{
    int freq1[27],freq2[27]; memset(freq1,0,sizeof(freq1)); memset(freq2,0,sizeof(freq2));
    int temp,mx1=0,mx2=0;
    for(temp=start;temp<=end;temp++)
    {
        if(temp%2==0)
        {
            freq1[a[temp]]++;
            mx1=max(mx1,freq1[a[temp]]);
        }
        else
        {
            freq2[a[temp]]++;
            mx2=max(mx2,freq2[a[temp]]);
        }
    }
    return mx1+mx2;
}
char buff[100000];
int main()
{
    int k;
    scanf("%d",&k);
    char*s;
    scanf("%s",&buff);
    s=strdup(buff);
    int n=strlen(s);
    int temp,temp2;
    for(temp=0;temp<n;temp++)
    {
        a[temp]=s[temp]-'a';
    }
    int start=0,end,mx=0,mx1=0,mx2=0;
    for(end=0;end<n;end++)
    {
        if(end%2==0)
        {
            allsum1[a[end]]++;
            mx1=max(mx1,allsum1[a[end]]);
        }
        else
        {
            allsum2[a[end]]++;
            mx2=max(mx2,allsum2[a[end]]);
        }
        while(end-start+1 - mx1-mx2>k)
        {
            if(start%2==0)
            {
                if(allsum1[a[start]]==mx1)
                {
                    allsum1[a[start]]--;
                    mx1=0;
                    for(temp=0;temp<26;temp++)
                    {
                        mx1=max(mx1,allsum1[temp]);
                    }
                }
                else    allsum1[a[start]]--;
            }
            else
            {
                if(allsum2[a[start]]==mx2)
                {
                    allsum2[a[start]]--;
                    mx2=0;
                    for(temp=0;temp<26;temp++)
                    {
                        mx2=max(mx2,allsum2[temp]);
                    }
                }
                else    allsum2[a[start]]--;
            }
            start++;
        }
        mx=max(mx,end-start+1);
    }
    printf("%d\n", mx);
}





















































