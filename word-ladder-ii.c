#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#ifdef _MSC_VER
  #define strdup _strdup
#endif

#define MAX_SZ      1024
#define LADDER_SZ   1024
#define MAX_LADDERS 1024
#define TREE_SZ      512

#define WORDS_SZ    5096
#define NUM_TREES   WORDS_SZ


typedef char* string;


string * ladders[MAX_LADDERS]; 
int laddersSz = 0;
string ladder[LADDER_SZ];  
int ladderSz = 0;
int    tree[NUM_TREES][TREE_SZ];
int      sizes[NUM_TREES];
int      fb,
fe,
bb,
be,
te,
last;
string words[WORDS_SZ];
int  *cols;





void swap(char**nums, int i, int j) {
	char*t = nums[i];
	nums[i] = nums[j];
	nums[j] = t;
}
void findPath(int w) {
	ladder[ladderSz++] = words[w];
	if (w == last) {
		cols[laddersSz] = ladderSz;
        string*newladder=malloc(ladderSz*sizeof(string));
        for(int i=0;i<ladderSz;i++)newladder[i]=strdup(ladder[i]);
        ladders[laddersSz++] = newladder;//copy
	}
	else
		for (int i = 0; i<sizes[w]; i++) {
			int child = tree[w][i];
			findPath(child);
		}
	if (ladderSz >= 1 ) {
		ladderSz--;
	}
}
bool isNeighbor(char*w1, char*w2) {
	bool ret = false;
	for (int i = 0; w1[i]; i++)
		if (w1[i] != w2[i])
			if (ret)
				return false;
			else
				ret = true;
	return ret;
}
bool combine() {
	bool ret = false;
	for (int i = fb; i<fe; i++)
		for (int j = bb; j>be; j--)
			if (isNeighbor(words[i], words[j])) {
				ret = true;
				tree[i][sizes[i]++] = j;
			}
	return ret;
}
bool buildLevel(bool forward) {
	if (forward) {
		te = fe;
		for (int i = fb; i<fe; i++) {
			for (int j = fe; j <= be; j++) {
				if (isNeighbor(words[i], words[j])) {
					if (j < te) {
						tree[i][sizes[i]++] = j;
					}
					else {
						swap(words, j, te);
						tree[i][sizes[i]++] = te++;
					}
				}
			}
		}
		if (te == fe)
			return false;
		fb = fe, fe = te;
	}
	else {
		te = be;
		for (int i = bb; i>be; i--) {
			for (int j = be; j >= fe; j--) {
				if (isNeighbor(words[i], words[j])) {
					if (j>te) {
						tree[j][sizes[j]++] = i;
					}
					else {
						swap(words, j, te);
						tree[te][sizes[te]++] = i;
						te--;
					}
				}
			}
		}
		if (te == be)
			return false;
		bb = be, be = te;
	}
	return true;
}

char*** findLadders(char*beginWord, char*endWord, char**wordList, int wordListSize, int**columnSizes, int*returnSize) {
    int contains=0;
	for (int i = 0; i<wordListSize; i++) {
		char*word = wordList[i];
        if(strcmp(word, endWord)==0){
          contains=1;
          break;
        }
    }
    if(contains==0)
        return NULL;
    
    laddersSz = 0;
    ladderSz = 0;
	cols = malloc(256 * sizeof(int));
	memset(ladders,0,sizeof(ladders));
	memset(ladder,0,sizeof(ladder));
	memset(sizes, 0, sizeof(sizes));
	last = wordListSize + 1;
	memset(words, 0, sizeof(words));
	memset(tree, 0, sizeof(tree));
	fb = 0, fe = 1, bb = last, be = last - 1, te = 1;
	words[fb] = beginWord;
	words[bb] = endWord;
	for (int i = 0; i<wordListSize; i++) {
		char*word = wordList[i];
		words[te++] = word;
	}
	while (!combine())
		if (!buildLevel((bb - be) - (fe - fb)>0))
			goto end;
	findPath(0);
end:

  *columnSizes = cols;
  *returnSize = laddersSz;
   return ladders;
 
}

#if 0
int main() {
	char*begWord = strdup("hit");
	char*endWord = strdup("cog");
	char**wordList = malloc(6 * sizeof(char*));
	wordList[0] = strdup("hot");
	wordList[1] = strdup("dot");
	wordList[2] = strdup("dog");
	wordList[3] = strdup("lot");
	wordList[4] = strdup("log");
	wordList[5] = strdup("cog");
	int rv;
	int*columns;
	char***rez=findLadders(begWord, endWord, wordList, 6, &columns, &rv);
    for(int i=0;i<rv;i++){
        for(int j=0;j<columns[i];j++){
            printf("%s ", rez[i][j]);
        }
        printf("\n");
    }
	return 0;
}
#endif








