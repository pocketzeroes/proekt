typedef struct {
    char* s;
    char** res;
    int size;
} cache_item;

cache_item cache[1024];
int wptr, wdsize;
char** wd;

void cache_store(char* s, char** res, int size)
{
    cache_item* c = &cache[wptr++];
    c->s = s;
    c->res = res;
    c->size = size;
}

cache_item* find_cache(char* s)
{
    int i;
    for (i = 0; i < wptr; i++) {
        if (cache[i].s == s)
            return &cache[i];
    }
    return NULL;
}

int startswith(char* s, char* sub)
{
    int i = 0;
    while (sub[i] && sub[i] == s[i]) i++;
    return sub[i] ? 0 : i;
}

char** wordBreak2(char* s, int* returnSize) {
    cache_item* c = find_cache(s);
    if (c) {
        *returnSize = c->size;
        return c->res;
    }
    char** res = malloc(1024 * sizeof(char*));
    int i, j, pos, size2, rptr = 0;
    char **res2, *tmp;

    for (i = 0; i < wdsize; i++)
    {
        if (pos = startswith(s, wd[i]))
        {
            if (pos == strlen(s))
            {
                tmp = res[rptr++] = malloc(1024);
                strcpy(tmp, s);
                continue;
            }
            res2 = wordBreak2(s + pos, &size2);
            for (j = 0; j < size2; j++) {
                tmp = res[rptr++] = malloc(1024);
                memcpy(tmp, s, pos); tmp[pos] = ' '; strcpy(tmp+pos+1, res2[j]);
            }
        }
    }
    cache_store(s, res, rptr);
    *returnSize = rptr;
    return res;
}

char** wordBreak(char* s, char** wordDict, int wordDictSize, int* returnSize) {
    wptr = 0;
    wdsize = wordDictSize;
    wd = wordDict;
    return wordBreak2(s, returnSize);
}
