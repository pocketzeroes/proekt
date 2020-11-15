typedef struct {
}OrderedStream;
OrderedStream*gptr;

char*s[1020];
bool visit[1020];
int pos;

OrderedStream*orderedStreamCreate(int n){
    memset(visit, 0, sizeof(visit));
    pos = 1;
    return gptr;
}
char**orderedStreamInsert(OrderedStream*obj, int id, char*value, int*rsz){
    visit[id] = true;
    s[id] = strdup(value);
    int beg = pos;
    while(visit[pos])
        pos++;
    char**ans;
    int asz = pos-beg;
    ans = calloc(asz, sizeof(char*));
    for(int z=0;z<asz;z++)
      ans[z]=strdup(s[beg+z]);
   *rsz = asz;
    return ans;
}
void orderedStreamFree(OrderedStream*obj){
  ;
}
