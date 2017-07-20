typedef struct{}
AutocompleteSystem;
AutocompleteSystem*ptr;

char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

char**sent;
int*time;
char*cur; int curSz=0;
int gSz;

AutocompleteSystem* autocompleteSystemCreate(char** sentences, int* times){
    gSz=0;
    for(int i=0;sentences[i];i++){char*sentence = sentences[i];
        gSz++;
    }
    sent = sentences;
    time = times;
    cur  = "";
    return ptr;
}
char** autocompleteSystemInput(AutocompleteSystem*obj, char c, int*rsz){
    if (c == '#'){
        for (int i = 0; i < gSz; ++i){
            if(strcmp(sent[i], cur)==0){
                ++time[i];
                cur = ""; curSz=0;
                return NULL;
            }
        }
        gSz++;
        sent = realloc(sent, gSz*sizeof(char*));sent[gSz-1]=strdup(cur);
        time = realloc(time, gSz*sizeof(int)); time[gSz-1]=1;
        cur = ""; curSz=0;
        return NULL;
    }

    curSz++;
    cur=realloc(cur, curSz);
    cur[curSz-1]=c;
    
    int l1 = -1, l2 = -1, l3 = -1;
    for (int i = 0; i < gSz; ++i){
        if(strncmp(sent[i], cur, curSz)==0){
            if      (l1 == -1 || time[l1] < time[i] || time[l1] == time[i] && strcmp(sent[i] , sent[l1])<0 ){l3 = l2; l2 = l1; l1 = i;}
            else if (l2 == -1 || time[l2] < time[i] || time[l2] == time[i] && strcmp(sent[i] , sent[l2])<0 ){l3 = l2; l2 = i;}
            else if (l3 == -1 || time[l3] < time[i] || time[l3] == time[i] && strcmp(sent[i] , sent[l3])<0 ){l3 = i;}
        }
    }
    int idx=0;
    char**ret=malloc(3*sizeof(char*));
    if (l1 != -1) ret[idx++] = sent[l1];
    if (l2 != -1) ret[idx++] = sent[l2];
    if (l3 != -1) ret[idx++] = sent[l3];
   *rsz=idx;
    return ret;
}






















