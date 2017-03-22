typedef struct TreeNode tn;
struct hash_map{
  int key;                
  int val; 
  UT_hash_handle hh;      
};
typedef struct hash_map map;
map* ht;
void htAdd(int key, int value) {
    map* s;
    HASH_FIND_INT(ht, &key, s);
    if (s==NULL) {
      s = (map*)malloc(sizeof(map));
      s->key = key;
      HASH_ADD_INT(ht, key, s);
    }
    s->val = value;
}
map* htFind(int key) {
    map* s;
    HASH_FIND_INT(ht, &key, s);
    return s;
}
void htCleanup(){
    map *cur, *tmp;
    HASH_ITER(hh, ht, cur, tmp)
    {
        HASH_DEL(ht, cur);
        free(cur);        
    }
}

tn* helper(int* preO, int* inO, int inS, int start, int end, int *posPreO)
{
  (*posPreO)++;
  if(end < start || *posPreO == inS)
  {
    (*posPreO)--;
    return NULL;  
  }
  map* htRet = htFind(preO[*posPreO]);
  if(htRet == NULL)
  {
    perror("something is wrong; the two lists do not match!");
    return NULL; 
  }
  int posInO  = htRet->val;
  tn* node    = (tn*)malloc(sizeof(tn));
  node->val   = preO[*posPreO];
  node->left  = helper(preO, inO, inS, start, posInO-1, posPreO);
  node->right = helper(preO, inO, inS, posInO+1, end,   posPreO);
  return node;
}

tn* buildTree(int* preO, int preS, int* inO, int inS)
{
  int posPreO = -1;            
  ht = NULL;                   
  for(int i = 0; i<inS; i++)
    htAdd(inO[i], i);          
  tn* res = helper(preO, inO, inS, 0, inS-1, &posPreO);
  htCleanup();
  return res;
}








