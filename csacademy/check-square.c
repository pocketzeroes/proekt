#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

double Sqrt(double x) {
  __asm__ ("fsqrt" : "+t" (x));
  return x;
}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}
//////////////////////////
int x[4], y[4];

double dist(int i, int j){
	int xx = (x[i]-x[j]);
	int yy = (y[i]-y[j]);
	return Sqrt(xx*xx + yy*yy);
}
bool run(){
	for(int i = 0; i < 4; ++i)
        scanf("%d %d", x+i, y+i);
	int pos[] = {0, 1, 2, 3};
	do{
		double d1 = dist(pos[0], pos[1]);
		double d2 = dist(pos[1], pos[2]);
		double d3 = dist(pos[2], pos[3]);
		double d4 = dist(pos[3], pos[0]);
		if(dist(pos[0], pos[1]) == dist(pos[1], pos[2]) && dist(pos[1], pos[2]) == dist(pos[2], pos[3]) && dist(pos[2], pos[3]) == dist(pos[3], pos[0]))
            return true;
	}
    while(next_permutation(pos, 4));
	return false;
}
int main() {
	int tc;
	scanf("%d", &tc);
	while(tc--){
		if(run())
            puts("1");
		else 
            puts("0");
	}
	return 0;
}




