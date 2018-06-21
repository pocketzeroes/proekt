#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}


#define SIZE 65
typedef long long ll;
int A  [SIZE];
int B  [SIZE];
int ord[SIZE];
int n,K;
vec ans;

void print(){
    printf("%d\n", ans.sz);
    for(int i=0;i<ans.sz; i++){
        if(i!=0)
            printf(" ");
        printf("%d", ans.ptr[i]+1);
    }
    puts("");
}
void swap3(int x){
    int y=x+1,z=x+2;
    if(x==0){
        for(int t=0;t<2;t++){
            for(int i=0;i<K-1;i++) ans.ptr=pushback(ans.ptr, &ans.sz, 1);
            for(int i=0;i<K-1;i++) ans.ptr=pushback(ans.ptr, &ans.sz, 0);
            for(int i=0;i<2;  i++) ans.ptr=pushback(ans.ptr, &ans.sz, 1);
        }
    }
    else{
        int s=max(1,z-K+1);
        for(int i=z;i<s+K-1;i++)
            ans.ptr=pushback(ans.ptr, &ans.sz, s);
        ans.ptr=pushback(ans.ptr, &ans.sz, s-1);
        ans.ptr=pushback(ans.ptr, &ans.sz, s);
        for(int i=0;i<K-2;i++) ans.ptr=pushback(ans.ptr, &ans.sz, s-1);
        for(int i=s;i<=z ;i++) ans.ptr=pushback(ans.ptr, &ans.sz, s);
    }
    swap(A, x, y);
    swap(A, y, z);
}
int main(){
    scanf("%d %d",&n,&K);
    for(int i=0;i<n;i++) 
        scanf("%d",&A[i]);
    for(int i=0;i<n;i++) 
        scanf("%d",&B[i]);
    if(n==K){
        for(int i=0;i<n;i++){
            if(A[0]!=B[0]){
                ans.ptr=pushback(ans.ptr, &ans.sz, 0);
                int x=A[n-1];
                for(int t=n-1;t>0;t--) 
                    A[t]=A[t-1];
                A[0]=x;
            }
            else{
                bool up=true;
                for(int t=0;t<n;t++) 
                    if(A[t]!=B[t]) 
                        up=false;
                if(!up){
                    puts("-1");
                    return 0;
                }
                print();
                return 0;
            }
        }
        puts("-1");
        return 0;
    }
    int ia=0,ib=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(A[i]>A[j])
                ia++;
            if(B[i]>B[j])
                ib++;
        }
    }
    if(ia%2!=ib%2){
        if(K%2==1){
            puts("-1");
            return 0;
        }
        ans.ptr=pushback(ans.ptr, &ans.sz, 0);
        int x=A[K-1];
        for(int t=K-1;t>0;t--) 
            A[t]=A[t-1];
        A[0]=x;
    }
    for(int i=n-1;i>=0;i--){
        int p=0;
        for(int j=0;j<n;j++) 
            if(A[j]==B[i]) 
                p=j;
        while(p<i){
            if(p+2<=i){
                swap3(p);
                p+=2;
            }
            else{
                swap3(p-1);
                swap3(p-1);
                break;
            }
        }
    }
    print();
    return 0;
}
