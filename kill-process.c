#ifndef __HASHMAP_H__
#define __HASHMAP_H__
#define MAP_MISSING -3
#define MAP_FULL -2
#define MAP_OMEM -1
#define MAP_OK 0
typedef void *any_t;
typedef int (*PFany)(any_t, any_t);
typedef any_t map_t;
map_t hashmap_new();

int hashmap_put(map_t in, int key, int value);
int hashmap_get(map_t in, int key, int*arg);

void hashmap_free(map_t in);
int hashmap_length(map_t in);
#endif
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_SIZE 1024
typedef struct _hashmap_element{
    int key;
    int in_use;
    int data;
} hashmap_element;
typedef struct _hashmap_map{
    int table_size;
    int size;
    hashmap_element *data;
} hashmap_map;
map_t hashmap_new() {
    hashmap_map* m = (hashmap_map*) malloc(sizeof(hashmap_map));
    if(!m) goto err;
    m->data = (hashmap_element*) calloc(INITIAL_SIZE, sizeof(hashmap_element));
    if(!m->data) goto err;
    m->table_size = INITIAL_SIZE;
    m->size = 0;
    return m;
  err:
    if (m)
        hashmap_free(m);
    return NULL;
}
unsigned int hashmap_hash_int(hashmap_map * m, unsigned int key){
    key += (key << 12);
    key ^= (key >> 22);
    key += (key << 4);
    key ^= (key >> 9);
    key += (key << 10);
    key ^= (key >> 2);
    key += (key << 7);
    key ^= (key >> 12);
    key = (key >> 3) * 2654435761;
    return key % m->table_size;
}
int hashmap_hash(map_t in, int key){
    int curr;
    int i;
    hashmap_map* m = (hashmap_map *) in;
    if(m->size == m->table_size) return MAP_FULL;
    curr = hashmap_hash_int(m, key);
    for(i = 0; i< m->table_size; i++){
        if(m->data[curr].in_use == 0)
            return curr;
        if(m->data[curr].key == key && m->data[curr].in_use == 1)
            return curr;
        curr = (curr + 1) % m->table_size;
    }
    return MAP_FULL;
}
int hashmap_rehash(map_t in){
    int i;
    int old_size;
    hashmap_element* curr;
    hashmap_map *m = (hashmap_map *) in;
    hashmap_element* temp = (hashmap_element *) calloc(2 * m->table_size, sizeof(hashmap_element));
    if(!temp) return MAP_OMEM;
    curr = m->data;
    m->data = temp;
    old_size = m->table_size;
    m->table_size = 2 * m->table_size;
    m->size = 0;
    for(i = 0; i < old_size; i++){
        int status = hashmap_put(m, curr[i].key, curr[i].data);
        if (status != MAP_OK)
            return status;
    }
    free(curr);
    return MAP_OK;
}
int hashmap_put(map_t in, int key, int value){
    int index;
    hashmap_map* m;
    m = (hashmap_map *) in;
    index = hashmap_hash(in, key);
    while(index == MAP_FULL){
        if (hashmap_rehash(in) == MAP_OMEM) {
            return MAP_OMEM;
        }
        index = hashmap_hash(in, key);
    }
    m->data[index].data = value;
    m->data[index].key = key;
    m->data[index].in_use = 1;
    m->size++;
    return MAP_OK;
}
int hashmap_get(map_t in, int key, int*arg){
    int curr;
    int i;
    hashmap_map* m;
    m = (hashmap_map *) in;
    curr = hashmap_hash_int(m, key);
    for(i = 0; i< m->table_size; i++){
        if(m->data[curr].key == key && m->data[curr].in_use == 1){
            *arg = (m->data[curr].data);
            return MAP_OK;
        }
        curr = (curr + 1) % m->table_size;
    }
    *arg = 0;
    return MAP_MISSING;
}
void hashmap_free(map_t in){
    hashmap_map* m = (hashmap_map*) in;
    free(m->data);
    free(m);
}
int hashmap_length(map_t in){
    hashmap_map* m = (hashmap_map *) in;
    if(m != NULL) return m->size;
    else return 0;
}
////
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int*ans;
int ansSz;
int*killProcess(int* pid, int pidSz, int* ppid, int ppidSize, int kill, int* retSz){
    if(ans){free(ans);ans=NULL;}
    ansSz=0;
    map_t pp = hashmap_new();
    int n = pidSz, i, j, k, ti;
    for (i = 0; i < n; i++)
      hashmap_put(pp, pid[i], i);
    for (i = 0; i < n; i++) {
        ti = i;
        while(1){
            k = pid[ti];
            if (k == kill) {
                ans = pushback(ans, &ansSz, pid[i]);
                break;
            }
            if (ppid[ti] == 0) 
                break;
            int rv;
            hashmap_get(pp,ppid[ti], &rv);
            ti = rv;
        }
    }
   *retSz=ansSz;
    return ans;
}







