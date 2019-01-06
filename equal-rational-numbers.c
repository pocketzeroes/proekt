typedef struct fenshu{
    int fenzi;
    int fenmu;
}fenshu;
int pows[5]={1,10,100,1000,10000};

int gcd(int x,int y){
    return y==0?x:gcd(y,x%y);
}
fenshu normals(fenshu f){
    int g=gcd(f.fenzi,f.fenmu);
    f.fenzi=f.fenzi/g;
    f.fenmu=f.fenmu/g;
    return f;
}
fenshu adds(fenshu x,fenshu y){
    int g=gcd(x.fenmu,y.fenmu);
    int l=x.fenmu/g*y.fenmu;
    x.fenzi=x.fenzi*(l/x.fenmu);
    y.fenzi=y.fenzi*(l/y.fenmu);
    x.fenzi=x.fenzi+y.fenzi;
    x.fenmu=l;
    return x;
}
fenshu deal(char*s){
    int len=strlen(s);
    int add=0;
    int f=0;
    for(f=0;f<len;f++){
        if(s[f]=='.')
            break;
        add=add*10+(s[f]-'0');
    }
    fenshu res;
    if(f<len-1){
        f++;
        int fix=0;
        int addf=0;
        for(;f<len;f++){
            if(s[f]=='(')
                break;
            fix++;
            addf=addf*10+(s[f]-'0');
        }
        res.fenzi=addf;
        res.fenmu=pows[fix];
        res=normals(res);
        if(f<len-1){
            f++;
            int cyc=0,ll=0;
            for(;f<len;f++){
                if(s[f]==')')
                    break;
                ll++;
                cyc=cyc*10+(s[f]-'0');
            }
            fenshu more;
            more.fenzi=cyc;
            more.fenmu=(pows[ll]-1)*pows[fix];
            more=normals(more);
            res=adds(res,more);
            res=normals(res);
        }
    }
    else{
        res.fenzi=0;
        res.fenmu=1;
    }
    res.fenzi=res.fenzi+res.fenmu*add;
    return res;
}
bool isRationalEqual(char*S, char*T){
    fenshu s=deal(S),
           t=deal(T);
    return s.fenzi==t.fenzi&&
           s.fenmu==t.fenmu;
}
