#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int rnk[256]={0};



int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    int Asize=strlen(*ia);
    int Bsize=strlen(*ib);
    int i=0,j=0;
    char*A=(char*)*ia;
    char*B=(char*)*ib;
    while(i<Asize && j<Bsize )
    {
        if(rnk[ A[i] ]<rnk[ B[j] ])
            return -1;
        else if(rnk[ A[i] ]>rnk[ B[j]])
            return 1;
        i++;
        j++;
    }
    return Asize<Bsize?-1:1;
} 

int main()
{
    char*A=NULL;
    size_t len;
    getline(&A, &len, stdin);
    for(int i=0;i<26;i++)
    {
        rnk[A[i]]=i;
        rnk[toupper(A[i])]=26+i;
    }
    int n;
    scanf("%d",&n);
    getchar();
    char**strings=malloc(n*sizeof(char*));
    for(int i=0;i<n;i++)
    {
      char str [500];
      scanf ("%499s",str);
      strings[i]=strdup(str);
    }
    qsort(strings, n, sizeof(char *), cstring_cmp);
    for(int i=0;i<n;i++)
        puts(strings[i]);
}














