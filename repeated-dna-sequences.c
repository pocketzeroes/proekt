#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CCOUNT            4
#define SEQUENCE_LEN      10
#define MAX_BLOCK_CNT     1024
#define ALLOC_SEGMENT_CNT 64
struct PrivateStack
{
    unsigned char *ptr;
    unsigned char *top;
    unsigned char *end;
    int            ent_sz;
};
void *StackAlloc(unsigned int size, unsigned int esize)
{
    struct PrivateStack *p;
    unsigned int slen = size * esize;
    p = malloc(sizeof(struct PrivateStack) + (slen * sizeof(unsigned char)));
    if (!p)
        return NULL;
    p->ptr = (unsigned char *)(p + 1);
    p->top = p->ptr;
    p->end = p->ptr + slen;
    p->ent_sz = esize;
    return p;
}
void StackFree(void *handle)
{
    free(handle);
}
int StackPush(void *handle, void *ptr)
{
    struct PrivateStack *p = handle;
    if ((!handle || !ptr) || (p->top + p->ent_sz > p->end))
        return -1;
    memcpy(p->top, ptr, p->ent_sz);
    p->top += p->ent_sz;
    return 0;
}
int StackPop(void *handle, void *ptr)
{
    struct PrivateStack *p = handle;
    if (!handle || !ptr || (p->top == p->ptr))
        return -1;
    p->top -= p->ent_sz;
    memcpy(ptr, p->top, p->ent_sz);
    return 0;
}
int StackEmpty(void *handle)
{
    struct PrivateStack *p = handle;
    if (!handle)
        return -1;
    return (p->top == p->ptr) ? 1 : 0;
}
struct SAllocInf
{
    int off;
    int bsz;
    unsigned char *buf;
    void *stack;
};
void *InitSAlloc(int bsz, int block_count)
{
    struct SAllocInf *salloc = NULL;
    if (bsz > 1 && block_count > 1 &&
        (salloc = calloc(1, sizeof(struct SAllocInf))) &&
        (salloc->stack = StackAlloc(block_count, sizeof(char *))) &&
        (salloc->buf = calloc(bsz, sizeof(char))))
        salloc->bsz = bsz;
    else if (salloc) {
        if (salloc->stack)
            StackFree(salloc->stack);
        if (salloc->buf)
            free(salloc->buf);
        free(salloc);
        salloc = NULL;
    }
    return salloc;
}
void *GetSAlloc(void *handle, int val)
{
    struct SAllocInf *salloc = handle;
    if (!handle || val < 1)
        return NULL;
    if (salloc->off + val >= salloc->bsz) {
        if (StackPush(salloc->stack, &salloc->buf))
            return NULL;
        if (!(salloc->buf = calloc(salloc->bsz, sizeof(char))))
            return NULL;
        salloc->off = 0;
    }
    salloc->off += val;
    return &salloc->buf[salloc->off - val];
}
void FreeSAlloc(void *handle)
{
    void *ptr;
    struct SAllocInf *salloc = handle;
    if (!handle) return;
    while (!StackEmpty(salloc->stack)) {
        StackPop(salloc->stack, &ptr);
        free(ptr);
    }
    if (salloc->buf)
        free(salloc->buf);
    free(salloc);
}
struct TrieNode
{
    struct TrieNode *cptr[CCOUNT];
    int word;
};
struct TrieNode *AddToTrie(struct TrieNode *root, char *str, int count, int *map, void *salloc)
{
    int off;
    if (!count)
        return root;
    off = map[*str - 'A'];
    if (!root->cptr[off] &&
        !(root->cptr[off] = GetSAlloc(salloc, sizeof(struct TrieNode))))
        return NULL;
    return AddToTrie(root->cptr[off], str + 1, count - 1, map, salloc);
}
char** findRepeatedDnaSequences(char* s, int* returnSize)
{
    char **str   = NULL;
    void *salloc = NULL;
    char *sarr;
    struct TrieNode *root = NULL, *node;
    int len = strlen(s), i;
    int map[26];
    if (!returnSize || !(root = calloc(1, sizeof(struct TrieNode))) ||
        !(salloc = InitSAlloc(sizeof(struct TrieNode) * ALLOC_SEGMENT_CNT, MAX_BLOCK_CNT)) ||
        !(str    = malloc(sizeof(char *) * len)))
            goto bahur;
    map[0] = 0, map[2] = 1, map[6] = 2, map[19] = 3;
    *returnSize = 0;
    for (i = 0; i <= len - SEQUENCE_LEN; ++i)
    {
        if (!(node = AddToTrie(root, &s[i], SEQUENCE_LEN, map, salloc)))
            goto bahur;
        if (node->word == 1)  {
            if (!(sarr = malloc(sizeof(char) * (SEQUENCE_LEN + 1))))
                goto bahur;
            strncpy(sarr, &s[i], SEQUENCE_LEN);
            sarr[SEQUENCE_LEN] = 0;
            str[*returnSize] = sarr;
            (*returnSize) += 1;
        }
        node->word++;
    }
  bahur:
    if (salloc)
        FreeSAlloc(salloc);
    if (root) free(root);
    return str;
}



