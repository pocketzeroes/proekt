int calcnext(unsigned long long *bin,int n)
{
    (*bin)+=1;
    return !((*bin)&(1<<n));
}
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
int** subsets(int* A, int n, int** col, int* s) {
    unsigned long long bin=0;int next=1;
    *col=(int *) malloc(sizeof(int)*1000000);
    int **X=(int **)malloc(sizeof(int *)*1000000);
    *s=0;
    qsort(A,n,sizeof(int),cmp);
    while (next){
        int i,p=0;
        X[*s]=(int *)malloc(sizeof(int)*n);
        for (i=0;i<n;i++)
        {
            if(bin&(1<<i))
                X[*s][p++]=A[i];
        }
        (*col)[*s]=p;
        (*s)++;
        next=calcnext(&bin,n);
    }
    return X;
}
