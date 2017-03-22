struct hash_map
{
  int key;
  int val;
  UT_hash_handle hh;
};
typedef struct hash_map map;
map* cache = NULL;
map* cacheFind(int key);
void cacheCleanup();
void cachePrint();
void cacheInvalidate();
map* cacheAging(map* lastUsed);
int totalSize, used;
typedef map LRUCache;

map*lRUCacheCreate(int capacity)
{
  cache = NULL;
  totalSize = capacity;
  used = 0;
  return cache;
}
void lRUCacheFree(LRUCache* obj)
{
  cacheCleanup();
  used = 0;
}
int lRUCacheGet(LRUCache* obj, int key)
{
  map* s = cacheFind(key);
  if(s == NULL)    return -1;
  else
  {
    s = cacheAging(s);
    return s->val;
  }
}
void lRUCachePut(LRUCache* obj, int key, int value)
{
  map* s;
  HASH_FIND_INT(cache, &key, s); 
  if (s!=NULL)
  {
    s = cacheAging(s);
  }
  else
  {
    if(used == totalSize)
      cacheInvalidate();  
    s = (map*)malloc(sizeof(map));
    s->key = key;
    HASH_ADD_INT(cache, key, s);
    used++;
  }
  s->val = value;
}
map* cacheAging(map* lastUsed)
{
  int key   = lastUsed->key;
  int value = lastUsed->val;
  HASH_DEL(cache, lastUsed);
  free(lastUsed);
  map* s = (map*)malloc(sizeof(map));
  s->key = key;
  s->val = value;
  HASH_ADD_INT(cache, key, s);
  return s;
}
void cacheInvalidate()
{
  map* s = cache;
  HASH_DEL(cache,s);
  free(s);
  used--;
}
map* cacheFind(int key)
{
    map* s;
    HASH_FIND_INT(cache, &key, s);  
    return s;
}
void cacheCleanup()
{
  map* cur, *tmp;
  HASH_ITER(hh, cache, cur, tmp)
  {
    HASH_DEL(cache, cur); 
    free(cur);         
  }
}
void cachePrint()
{
    map* s;
    for(s=cache; s != NULL; s=(map*)(s->hh.next))
      printf("key %d:  value %d\n", s->key, s->val);
}


















