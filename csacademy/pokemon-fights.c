#include<stdio.h>

int n, i, a[110],b[110], tmp;
int main(){
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(i==0)
            continue;
		if(i!=0&&a[tmp]<a[i])
            tmp=i;
		b[tmp]++;
	}
	for(i=0;i<n;i++)
        printf("%d ",b[i]);
}
