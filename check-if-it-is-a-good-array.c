int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
bool isGoodArray(int*a, int aSz){
    int g=a[0];
    for(int z=0;z<aSz;z++){int i=a[z];
        g=gcd(i,g);
    }
    if(g==1)
        return 1;
    return 0;
}
