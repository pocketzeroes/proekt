#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 

char s[100000];
char a[100000];
char b[100000];
int main(){
	scanf("%s", &s);
	scanf("%s", &a);
	scanf("%s", &b);
	int l = strlen(a);
    int ssize=strlen(s);
	for(int i=0;i < ssize;){
		char*t = substr(s, i, l);
		if(strcmp(t, a)==0){
			puts(b);
			i+=l;
		}
		else if(strcmp(t, b)==0){
			puts(a);
			i+=l;
		}
		else{
			putchar(s[i]);
			i++;
		}
	}
	puts("");
	return 0;
}























































