typedef struct node{
  char c;
  int  a[26];
}node;
node a[26];
int cmpn(const void*pa, const void*pb){
  node*x=(node*)pa;
  node*y=(node*)pb;
  for(int i=0; i<26; i++)
    if(x->a[i]!=y->a[i])
      return(x->a[i]>y->a[i])?-1:1;
  return(x->c<y->c)?-1:1;
}
char ans[27];
int  asz;
char*rankTeams(char**votes, int votesSz){
  asz=0;
  int m = strlen(votes[0]),i;
  memset(a, 0, sizeof(a));
  for(i=0; i<26; i++)
    a[i].c=i+'A';
  for(int z=0;z<votesSz;z++){char*v=votes[z];
    for(i=0; i<m; i++)
      a[v[i]-'A'].a[i]++;
  }
  qsort(a, 26, sizeof(node), cmpn);
  for(i=0; i<m; i++)
    ans[asz++] = a[i].c;
  ans[asz] = '\0';
  return strdup(ans);
}
