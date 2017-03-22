#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct {
    char *word;
    int occurs;
} wordEntry;

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int *result = NULL;
    *returnSize = 0;
    if (wordsSize <= 0)
        return result;
    int slength = strlen(s), wlength = strlen(words[0]);
    if (slength < wlength * wordsSize)
        return result;
    wordEntry *ws = newArray(wordEntry, wordsSize);
    int wsSize = 0, i, j, k;
    for (i = 0; i < wordsSize; ++i) {
        char *word = words[i];
        for (k = -1, j = 0; k < 0 && j < wsSize; ++j)
            if (strcmp(ws[j].word, word) == 0)
                k = j;
        if (k < 0)
            k = wsSize++;
        ws[k].word = word;
        ws[k].occurs++;
    }
    slength -= wlength - 1;
    int *ms = newArray(int, slength);
    for (i = 0; i < slength; ++i) {
        for (k = -1, j = 0; k < 0 && j < wsSize; ++j)
            if (strncmp(s + i, ws[j].word, wlength) == 0)
                k = j;
        ms[i] = k;
    }
    int *os = newArray(int, wordsSize);
    for (i = 0; i < wlength; ++i) {
        int start = i, found = 0;
        for (j = i; j < slength; j += wlength) {
            int windex = ms[j];
            if (windex < 0) {
                start = j + wlength;
                while (found > 0) {
                    ws[os[--found]].occurs++;
                }
                continue;
            }
            if (ws[windex].occurs == 0) {
                for (k = 0; k < found; ++k) {
                    ws[os[k]].occurs++;
                    start += wlength;
                    if (os[k] == windex) {
                        ++k;
                        break;
                    }
                }
                found -= k;
                if (found)
                    memmove(os, os + k, found * sizeof(*os));
            }
            ws[windex].occurs--;
            os[found++] = windex;
            if (found == wordsSize)
                result = pushback(result, returnSize, start);
        }
        while (found > 0) {
            ws[os[--found]].occurs++;
        }
    }
    free(ws);
    free(ms);
    free(os);
    return result;
}



