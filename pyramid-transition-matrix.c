#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
enum{   SIZE =(int) 1e6+10};
int vv [SIZE];
int d  [26][ 26];
int lv [ 2][111];

int get_bit(int x,int v){
    return (x>>v)&1;
}
bool pyramidTransition(char*bb, char**allowed, int allowedSz){
    memset((d),  0, sizeof((d)) );
    memset((lv), 0, sizeof((lv)));
    for(int z=0; z<allowedSz; z++){char*s = allowed[z];
        d[s[0]-'A'][s[1]-'A'] |= 1<<(s[2]-'A');
    }
    int n=strlen(bb);
    for (int i = 0; i < (n); ++i){
        lv[0][i]=1<<(bb[i]-'A');
    }
    int now=0,nxt=1;
    for(int i=n;i>1;i--){
        memset((lv[nxt]), 0, sizeof((lv[nxt])));
        for (int j = 0; j < (i-1); ++j){
            for (int k1 = 0; k1 < (7); ++k1)for (int k2 = 0; k2 < (7); ++k2){
                if(get_bit(lv[now][j  ],k1)&&
                   get_bit(lv[now][j+1],k2)){
                    lv[nxt][j]|=d[k1][k2];
                }
            }
        }
        swap(now, nxt);
    }
    return lv[now][0]!=0;
}
