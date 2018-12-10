int a[100005],b[100005];

bool canReorderDoubled(int*A, int Asz){
    int i;
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(i=0;i<Asz;i++)
        if(A[i]<0)
            a[-A[i]]++;
    else
        b[A[i]]++;
    for(i=1;i<=50000;i++)
        if(a[i])
            if(a[i*2]<a[i])
                return 0;
    else{
        a[i*2]-=a[i];
        a[i]=0;
    }
    for(;i<=100000;i++)
        if(a[i])
            return 0;
    for(i=1;i<=50000;i++)
        if(b[i])
            if(b[i*2]<b[i])
                return 0;
    else{
        b[i*2]-=b[i];
        b[i]=0;
    }
    for(;i<=100000;i++)
        if(b[i])
            return 0;
    return !(b[0]&1);
}
