typedef struct{
} TreeAncestor;
TreeAncestor*gptr;
enum{MAXD = 16};
int anc[50005][MAXD];

TreeAncestor*treeAncestorCreate(int n, int* parent, int parentSz){
  for(int i=0; i<n; i++)
    anc[i][0] = parent[i];
  for(int d=1; d<MAXD; d++)
    for(int i=0; i<n; i++){
      if(anc[i][d-1] == -1)
        anc[i][d] = -1;
      else
        anc[i][d] = anc[anc[i][d-1]][d-1];
    }
  return gptr;
}
int treeAncestorGetKthAncestor(TreeAncestor* obj, int node, int k) {
  for(int d = MAXD-1; d >= 0; d--){
    if((1<<d) <= k){
      k -= 1 << d;
      node = anc[node][d];
      if(node == -1)
        return node;
    }
  }
  return node;
}
void treeAncestorFree(TreeAncestor* obj) {
  ;
}
