#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void random_shuffle(int*gCopy, int gSize) {
    for (int i = 0;i < gSize;i++){
        int pos = rand()%(gSize-i);
        swap(gCopy, i+pos, i);
    }
}

int f(int*t,int tsize, bool hi) {
    if(tsize ==1) return t[0];
    if(tsize ==2) {
		printf("Q 1 1 %d %d\n", t[0], t[1]);fflush(stdout);
		int aa;
		scanf("%d", &aa);
		if((aa==1 && hi) || (aa==-1 && !hi))  {
			return t[0];
		}else if((aa==1 && !hi) || (aa==-1 && hi)) {
			return t[1];
		}
		return -1;
	}
    int*a=NULL;int aSz=0;
    int*b=NULL;int bSz=0;
    int*c=NULL;int cSz=0;
    for(int i=0;i<(tsize/3);++i) {
        a = pushback(a, &aSz, t[i]);
    }
    for(int i=tsize/3;i<(2*(tsize/3));++i) {
        b = pushback(b, &bSz, t[i]);
    }
    for(int i=2*(tsize/3);i<tsize;++i) {
		c = pushback(c, &cSz, t[i]);
	}
	printf("Q %d %d ", aSz, bSz );fflush(stdout);
    for(int z=0;z<aSz;z++){int i=a[z];printf("%d ", i); fflush(stdout);}
    for(int z=0;z<bSz;z++){int i=b[z];printf("%d ", i); fflush(stdout);}
	puts("");fflush(stdout);
	int ans;
	scanf("%d", &ans);
	if(!ans) return f(c,cSz,hi);
	if(ans==-1) {
		if(hi) {
			return f(b,bSz,hi);
		}else {
			return f(a,aSz,hi);
		}
	}
	if(hi) {
		return f(a,aSz,hi);
	}
	return f(b,bSz,hi);
}
int main() {
    int n;
    scanf("%d", &n);
    int mid=-1;
    int a,b,c;
    puts("Q 1 1 1 2");fflush(stdout); scanf("%d", &a);
    puts("Q 1 1 2 3");fflush(stdout); scanf("%d", &b);
    puts("Q 1 1 1 3");fflush(stdout); scanf("%d", &c);
    if(!c) mid=1;
    else if(!a) mid=1;
    else if(!b) mid=2;
    else {
        if(a==-1 && b==-1) {
            mid=2;
        }else if(a==1 && b==1) {
            mid=2;
        }else if(a==1 && c==-1) {
            mid=1;
        } else if(a==-1 && c==1) {
            mid=1;
        }else if(a==-1 && b==1) {
            mid=3;
        }else if(a==1 && b==-1) {
            mid=3;
        }
    }
    int curr[n];
    int currLen=0;
    for(int i=1;i<=n;++i) {
        if(n&1 && mid==i) continue ;
        curr[currLen++] = i;
    }
    int*hi=NULL;int hiSz=0;
    int*lo=NULL;int loSz=0;
    while(1) {
        random_shuffle(curr, currLen);
        for(int i=0;i<(currLen/2);++i) {
            lo = pushback(lo,&loSz, curr[i]          );
            hi = pushback(hi,&hiSz, curr[i+currLen/2]);
        }
        printf("Q %d %d ", loSz, hiSz);fflush(stdout);
        for(int z=0;z<loSz;z++){int i=lo[z];printf("%d ", i); fflush(stdout);}
        for(int z=0;z<hiSz;z++){int i=hi[z];printf("%d ", i); fflush(stdout);}
        puts("");fflush(stdout);
        int ans;
        scanf("%d", &ans);
        if(ans!=0) {
            if(ans==1){
                int*tmp;
                tmp = lo ;
                lo  = hi ;
                hi  = tmp;
                int ttLen;
                ttLen= loSz;
                loSz = hiSz;
                hiSz = ttLen;
            }
            break ;
        }
    }
	int low =f(lo, loSz, false); 
    int high=f(hi, hiSz, true );
	printf("A %d %d\n", low, high);fflush(stdout);
    return 0;
}





















































