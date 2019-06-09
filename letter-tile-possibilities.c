char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
int cmp(const void*pa, const void*pb){
  char*a =(char*)pa;
  char*b =(char*)pb;
  return(*a < *b)?-1:1;
}
int dfs(char*tiles, bool*is_visited, char*cur, int res, int n){
    if(strlen(cur)==n){
        res++;
        return res;
    }
    for(int i=0; tiles[i]; i++){
        if(is_visited[i])
            continue;
        if(i>0&&tiles[i]==tiles[i-1]&&is_visited[i-1]==0)
            continue;
        cur = concatc(cur, tiles[i]);
        is_visited[i] = 1;
        res = dfs(tiles, is_visited, cur, res, n);
        is_visited[i] = 0;
        cur[strlen(cur)-1] = '\0';
    }
    return res;
}
int numTilePossibilities(char*tiles){
    int tilessz = strlen(tiles);
    qsort(tiles, tilessz, sizeof(char), cmp);
    bool is_visited[tilessz]; memset(is_visited, 0, sizeof(is_visited));
    char*cur = strdup("");
    int res = 0;
    for(int i=1; i<=tilessz; i++)
        res = dfs(tiles, is_visited, cur, res, i);
    return res;
}
