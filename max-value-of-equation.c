typedef struct{
  int fi, se;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
void upmax(int*a, int b){
    if(*a < b)
       *a = b;
}
pair a[1001000];

int findMaxValueOfEquation(int**p, int pSz, int*p0sz, int k){
    int l = 0, 
        r = 0;
    int ans =(int) -1e9;
    for(int z=0;z<pSz;z++){int*po=p[z];
        int x = po[0], 
            y = po[1];
        while (l < r && x - a[l].fi > k)
            l++;
        if(l<r)
            upmax(&ans, x - a[l].fi + a[l].se + y);
        while (l < r) {
            int i = r - 1;
            if (-a[i].fi + a[i].se <= (-x + y))
                r--;
            else
                break;
        }
        a[r++] = newpair(x,y);
    }
    return ans;
}
