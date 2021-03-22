#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int tr[20005*20][2],cnt[20005*20],tot=0;
void insert(int x){
    int p=0;
    for(int i=15;i>=0;--i){
        int idx=x>>i&1;
        if(!tr[p][idx])
            tr[p][idx]=++tot;
        p=tr[p][idx];
        cnt[p]++;
    }
}
int query(int x, int hi){
    int ret=0,p=0;
    for(int i=15;i>=0;--i){
        int a=x>>i&1,h=hi>>i&1;
        if(a==0 && h==0){
            ret+=cnt[tr[p][1]];
            p=tr[p][0];
        }
        if(a==0 && h==1){
            p=tr[p][1];
        }
        if(a==1 && h==0){
            ret+=cnt[tr[p][0]];
            p=tr[p][1];
        }
        if(a==1 && h==1){
            p=tr[p][0];
        }
        if(!p)
            return ret;
    }
    return ret;
}
int countPairs(int*a, int aSz, int l, int h){
    clr(tr);
    clr(cnt);
    tot=0;
    for(int z=0;z<aSz;z++){int i=a[z];
        insert(i);
    }
    int ret=0;
    for(int z=0;z<aSz;z++){int i=a[z];
        ret+=query(i,l-1)-query(i,h);
    }
    return ret/2;
}
