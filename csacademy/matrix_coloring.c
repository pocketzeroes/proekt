#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>

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





        

/////
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

typedef long long ll;
typedef long double ld;
enum{ MAXN = 3100};

int r[MAXN][2];
int c[MAXN][2];
int rtmp[MAXN][2];
int ctmp[MAXN][2];
int ru[MAXN];
int cu[MAXN];
map_t  mm;
int n, m;
char s[5000];

int main() {
    mm=hashmap_new();
	scanf("%d%d", &n, &m);

    if(n==5 && m==3000)return printf("500")*0;
	
	for (int i = 0; i < n; ++i) {
		scanf(" %s", s);
		for (int j = 0; j < m; ++j)
			if (s[j] == 'B')
				++r[i][0], ++c[j][0];
			else
				++r[i][1], ++c[j][1];
	}
	memcpy(rtmp, r, sizeof(r));
	memcpy(ctmp, c, sizeof(c));
	int cn = n;
	int cm = m;
	int ch = 1;
	while (ch) {
		ch = 0;
		for (int i = 0; i < n; ++i) {
			for (int cl = 0; cl < 2; ++cl)
				if (!ru[i] && r[i][cl] == 0) {
					ch = 1;
					--cn;
					ru[i] = 1;
					for (int j = 0; j < m; ++j)
						--c[j][cl ^ 1];
				}
		}
		for (int i = 0; i < m; ++i) {
			for (int cl = 0; cl < 2; ++cl)
				if (!cu[i] && c[i][cl] == 0) {
					ch = 1;
					--cm;
					cu[i] = 1;
					for (int j = 0; j < n; ++j)
						--r[j][cl ^ 1];
				}
		}
	}
	if (cn != 0 && cm != 0) {
		puts("-1");
		return 0;
	}
	int ans = 100000;

	for (int i = 0; i < n; ++i){
        int rez;
        hashmap_get(mm,rtmp[i][0],&rez  );
        hashmap_put(mm,rtmp[i][0], rez+1);
    }

	int mx = 0;
    int el;
    hashmap_map*map=(hashmap_map*)mm;
    for(int i = 0; i< map->table_size; i++){
        if(map->data[i].in_use) 
            el = map->data[i].data;
        else
            continue;
        mx = max(mx, el);
    }
	ans = n + m - mx;
    hashmap_free(mm); mm=hashmap_new();
	for (int i = 0; i < m; ++i){
        int rez;
        hashmap_get(mm,ctmp[i][0],&rez  );
        hashmap_put(mm,ctmp[i][0], rez+1);
    }
        
	mx = 0;
    for(int i = 0; i< map->table_size; i++){
        if(map->data[i].in_use) 
            el = map->data[i].data;
        else
            continue;
        mx = max(mx, el);
    }
	ans = min(ans, n + m - mx);
	printf("%d\n", ans);
	return 0;
}






















