typedef struct {
	int *arr;
	int size;
	int len;
} RandomizedCollection;
#define RANDOMIZEDCOLLECTION_INITSIZE 8

RandomizedCollection* randomizedCollectionCreate() {
	RandomizedCollection* collection = malloc(sizeof(RandomizedCollection));
	if (collection==NULL)
		return NULL;
	collection->arr = malloc(sizeof(int)*RANDOMIZEDCOLLECTION_INITSIZE);
	collection->size = RANDOMIZEDCOLLECTION_INITSIZE;
	collection->len = 0;
	return collection;
}

bool randomizedCollectionInsert(RandomizedCollection* obj, int val) {
	bool ret = true;
	int lo=0, hi=obj->len-1;
	if (obj->len + 1 >= obj->size) {
		int* p = realloc(obj->arr, obj->size * 2 * sizeof(int));
		if (p == NULL)
			return false;
		obj->arr = p;
		obj->size = obj->size * 2;
	}
	int idx = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (obj->arr[mid] < val)
			lo = mid + 1;
		else if (obj->arr[mid] > val)
			hi = mid - 1;
		else {
			idx = mid;
			ret = false;
			break;
		}
	}
	if (idx == -1)
		idx = lo;
	int i;
	for (i=obj->len; i-1>=idx; i--)
		obj->arr[i] = obj->arr[i-1];
	obj->arr[idx] = val;
	obj->len ++;
	return ret;
}

bool randomizedCollectionRemove(RandomizedCollection* obj, int val) {
	int lo=0, hi=obj->len-1;
	int idx = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (obj->arr[mid] > val)
			hi = mid - 1;
		else if (obj->arr[mid] < val)
			lo = mid + 1;
		else {
			idx = mid;
			break;
		}
	}
	if (idx == -1)
		return false;
	int i;
	for (i=idx; i+1<obj->len; i++) {
		obj->arr[i] = obj->arr[i+1];
	}
	obj->len--;
	return true;
}

int randomizedCollectionGetRandom(RandomizedCollection* obj) {
	if (obj->len == 0)
		return 0;
	int r = rand() % obj->len;
	return obj->arr[r];
}

void randomizedCollectionFree(RandomizedCollection* obj) {
	if (obj != NULL) {
		if (obj->arr != NULL)
			free (obj->arr);
		free (obj);
	}
}





