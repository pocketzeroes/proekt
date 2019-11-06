#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

typedef struct{
    int w, h;
}Foo;
Foo a[4];

int cmp(const void*pa, const void*pb){
    Foo*a=(Foo*)pa;
    Foo*b=(Foo*)pb;
    if(a->w==b->w)
        return(a->h>b->h)?-1:1;
    return(a->w>b->w)?-1:1;
}
int main(){
    for(int i=1; i<=3; i++){
        scanf("%d %d", &a[i].w, &a[i].h);
        if(a[i].w < a[i].h)
            swap(a[i].w, a[i].h);
    }
    qsort(a+1, 3, sizeof(Foo), cmp);
    int flag=0;
    if(a[1].w==a[2].w&&a[2].w==a[3].w){
        if(a[1].h+a[2].h+a[3].h==a[1].w)
            flag=1;
    }
    else{
        if(a[2].w==a[3].w){
            if((a[2].h+a[3].h==a[1].w)&&(a[2].w+a[1].h==a[1].w))
                flag=1;
        }
        else if(a[2].h==a[3].h){
            if((a[2].w+a[3].w==a[1].w)&&(a[2].h+a[1].h==a[1].w))
                flag=1;
        }
        else if(a[2].w==a[3].h){
            if((a[2].h+a[3].w==a[1].w)&&(a[2].w+a[1].h==a[1].w))
                flag=1;
        }
        else if(a[2].h==a[3].w){
            if((a[2].w+a[3].h==a[1].w)&&(a[2].h+a[1].h==a[1].w))
                flag=1;
        }
    }
    if(flag==1)
        puts("YES");
    else
        puts("NO");
    return 0;
}
