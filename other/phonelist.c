#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tr{
	struct tr*next[10];
	bool end;
}trie;

trie*newtrie(){
  trie*rez = calloc(1, sizeof(trie));
  return rez;
}
int main(){
	int t, n, i, p;
	char str[15];
	bool flag;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		trie *head, *tail;
		head = newtrie();
		flag = 1;
		while(n--){
			scanf("%s", str);
			if(flag){
				tail = head;
				for(i=0; str[i]; i++){
					if(tail->end){
						flag = 0;
						break;
					}
					p = str[i]-'0';
					if(tail->next[p]==NULL)
            tail->next[p] = newtrie();
					tail = tail->next[p];
				}
				tail->end = 1;
				for(i=0; i<10; i++){
					if(tail->next[i]){
						flag = 0;
						break;
					}
				}
			}
		}
		if(flag) 
      printf("YES\n");
		else 
      printf("NO\n");
	}
	return 0;
}






















































