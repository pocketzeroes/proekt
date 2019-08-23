#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*to_string(int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d", v);
  return ptr;
}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
	char*ss=getstr();
	int n = strlen(ss);
	if(strcmp(ss, "0")==0)
        printf("0\n");
	else{
		int numlen = fmax(0, n - 7);
		while(1){
			char*nlstr = to_string(numlen + 1);
            int nlstr_sz = strlen(nlstr);
			int slen = nlstr_sz + numlen;
			if(slen > n)
                break;
			if(slen == n && strncmp(nlstr, ss, nlstr_sz)>0)
				break;
			numlen++;
		}
		bool leading = true;
		int cur = 0;
		for(int i=0;ss[i];i++){char c = ss[i];
			cur = 10 * cur + c - '0';
			int div = cur / numlen;
			cur %= numlen;
			if(div != 0){
				putchar(div + '0');
				leading = false;
			}
            else if(!leading)
                putchar('0');
		}
		puts("");
	}
    return 0;
}
