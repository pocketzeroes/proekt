#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>




int accumulate(int*arr, int sz){
  int sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}


inline int signum(double x){
    return(fabs(x) < 1.0e-10 ? 0 : x > 0 ? 1 : -1);
}
typedef struct{
    double x, y, z;
}pt;
pt newpt(double a, double b, double c){
    return(pt){a,b,c};
}
pt opAdd(pt a, pt o){
    return newpt(a.x+o.x, a.y+o.y, a.z+o.z);
}
pt opSub(pt a, pt o){
    return newpt(a.x-o.x, a.y-o.y, a.z-o.z);
}
pt opDiv(pt a, pt o){
    return newpt(fabs(o.x)<1.0e-10?0:a.x/o.x, fabs(o.y)<1.0e-10?0:a.y/o.y, fabs(o.z)<1.0e-10?0:a.z/o.z);
}
pt opDiv2(pt a, double o){
    return newpt(a.x/o, a.y/o, a.z/o);
}
pt opMul(pt a, double o){
    return newpt(a.x*o, a.y*o, a.z*o);
}
inline double inp(pt v1, pt v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
inline pt outp(pt p1, pt p2){
    return newpt(p1.y*p2.z - p1.z*p2.y, p1.z*p2.x - p1.x*p2.z, p1.x*p2.y - p1.y*p2.x);
}
inline double norm(pt v){
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

////////////////////////////

int n, T;
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        pt p[n];
        for(int i=0; i<n; i++){
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            p[i] = newpt(x, y, z);
        }
        int ans[n]; memset(ans,0, sizeof(ans));
        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                for(int k=0; k<j; k++){
                    pt q = outp(opSub(p[j],p[i]), opSub(p[k],p[i]));
                    int f = 1, t = 0;
                    if(norm(q) < 1.0e-10)
                        continue;
                    for(int l=0; l<n; l++){
                        int s = signum(inp(q, opSub(p[l], p[i])));
                        if(s && t && s != t)
                            f = 0;
                        if(!t)
                            t = s;
                    }
                    if(f)
                        ans[i]=ans[j]=ans[k]=1;
                }
            }
        }
        if(accumulate(ans, n) == 0){
            for(int i=0; i<n; i++)
                ans[i] = 1;
        }
        for(int i=0; i<n; i++)
            putchar(ans[i]?'T':'F');
        puts("");
    }
    return 0;
}
