#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#ifdef _MSC_VER
  #define strdup _strdup
#endif
#define MAX_CHARS     26
#define MAX_WORD_SIZE 30
typedef struct TrieNod{
    bool            isEnd;
    unsigned        frequency;
    int             indexMinHeap;
    struct TrieNod* child[MAX_CHARS];
}TrieNode;
typedef struct MinHeapNode_s{
    TrieNode* root;
    unsigned  frequency;
    char*     word;
}MinHeapNode;
typedef struct MinHeap_s{
    unsigned     capacity;
    int          count;
    MinHeapNode* array;
}MinHeap;


int cmpObj(const void*pa, const void*pb){
    MinHeapNode*a = (MinHeapNode*)pa;
    MinHeapNode*b = (MinHeapNode*)pb;
    if(a->frequency != b->frequency)
        return(a->frequency > b->frequency)?-1:1;
    return strcmp(a->word, b->word) < 0 ? -1 :1;
}


MinHeap*newMinHeap(){
    MinHeap*rez = malloc(sizeof(MinHeap));
    return rez;
}
MinHeapNode*newMinHeapNode(int cap){
    MinHeapNode*rez = calloc(cap, sizeof(MinHeapNode));
    return rez;
}
TrieNode* newTrieNode(){
    TrieNode* trieNode = calloc(1, sizeof(TrieNode));
    trieNode->isEnd = 0;
    trieNode->frequency = 0;
    trieNode->indexMinHeap = -1;
    for (int i = 0; i < MAX_CHARS; ++i)
        trieNode->child[i] = NULL;
    return trieNode;
}
MinHeap* createMinHeap(int capacity){
    MinHeap*minHeap = newMinHeap();
    minHeap->capacity = capacity;
    minHeap->count = 0;
    minHeap->array = newMinHeapNode(minHeap->capacity);
    return minHeap;
}
void swapMinHeapNodes(MinHeapNode*a, MinHeapNode*b){
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapify(MinHeap*minHeap, int idx){
    int left, right, smallest;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    smallest = idx;
    if (left < minHeap->count && minHeap->array[left].frequency < minHeap->array[smallest].frequency)
        smallest = left;
    if (right < minHeap->count && minHeap->array[right].frequency < minHeap->array[smallest].frequency)
        smallest = right;
    if (smallest != idx) {
        minHeap->array[smallest].root->indexMinHeap = idx;
        minHeap->array[idx].root->indexMinHeap = smallest;
        swapMinHeapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
void buildMinHeap(MinHeap* minHeap){
    int n, i;
    n = minHeap->count - 1;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
void insertInMinHeap(MinHeap* minHeap, TrieNode** root, const char* word){
    if ((*root)->indexMinHeap != -1) {
        ++(minHeap->array[(*root)->indexMinHeap].frequency);
        minHeapify(minHeap, (*root)->indexMinHeap);
    }
    else if (minHeap->count < (int) minHeap->capacity) {
        int count = minHeap->count;
        minHeap->array[count].frequency = (*root)->frequency;
        minHeap->array[count].word = strdup(word);
        minHeap->array[count].root = *root;
        (*root)->indexMinHeap = minHeap->count;
        ++(minHeap->count);
        buildMinHeap(minHeap);
    }
    else if ((*root)->frequency > minHeap->array[0].frequency) {
        minHeap->array[0].root->indexMinHeap = -1;
        minHeap->array[0].root = *root;
        minHeap->array[0].root->indexMinHeap = 0;
        minHeap->array[0].frequency = (*root)->frequency;
        free(minHeap->array[0].word);
        minHeap->array[0].word = strdup(word);
        minHeapify(minHeap, 0);
    }
}
void insertUtil(TrieNode** root, MinHeap* minHeap, const char* word, const char* dupWord){
    if (*root == NULL)
        *root = newTrieNode();
    if (*word != '\0')
        insertUtil(&((*root)->child[tolower(*word) - 97]), minHeap, word + 1, dupWord);
    else {
        if ((*root)->isEnd)
            ++((*root)->frequency);
        else {
            (*root)->isEnd = 1;
            (*root)->frequency = 1;
        }
        insertInMinHeap(minHeap, root, dupWord);
    }
}
void insertTrieAndHeap(const char*word, TrieNode** root, MinHeap* minHeap){
    insertUtil(root, minHeap, word, word);
}

char**topKFrequent(char**words, int wordsSz, int k, int*rsz){
    k += 6;
    MinHeap* minHeap = createMinHeap(k);
    TrieNode* root = NULL;
    for(int i=0; i<wordsSz; i++)
        insertTrieAndHeap(words[i], &root, minHeap);
    char**rezult = calloc(k, sizeof(char*));
    
    qsort(minHeap->array, minHeap->count, sizeof(MinHeapNode), cmpObj);
    
    for(int i = 0; i < minHeap->count; i++){
        rezult[i] = minHeap->array[i].word;
    }
    k -= 6;
   *rsz = k;
    return rezult;
}



