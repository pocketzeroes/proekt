typedef struct Entry {
	int number;
    int count;
	struct Entry * next;
}Entry;
typedef struct Hash {
    int frequency;
    int count;
    int bounds;
	Entry ** base;
}Hash;
Hash * createHash(int factor) {
	Hash * hash = malloc(sizeof(Hash));
    hash->frequency = 1;
    hash->count = 0;
    hash->bounds = factor;
	hash->base = malloc(sizeof(Entry *) * factor);
	int index;
	for (index = 0 ; index < factor ; ++index) {
		(hash->base)[index] = malloc(sizeof(Entry));
		(hash->base)[index]->number = -1;
		(hash->base)[index]->next = NULL;
	}
	return hash;
}
void destroyHash(Hash * hash) {
	int index;
	Entry * temp;
	for (index = 0 ; index < hash->bounds ; ++index) {
		while((hash->base)[index]->next) {
			temp = (hash->base)[index]->next;
			(hash->base)[index]->next = temp->next;
			free(temp);
		}
		free((hash->base)[index]);
	}
	free(hash->base);
	free(hash);
}
void hashInsert(Hash * hash, int number) {
	int index = labs(number) % hash->bounds;
	Entry * temp = (hash->base)[index]->next;
	while(temp) {
		if (temp->number == number) {
            temp->count++;
            if (temp->count == hash->frequency) {
                hash->count++;
            } else if (temp->count > hash->frequency) {
                hash->frequency = temp->count;
                hash->count = 1;
            }
            return;
        }
		temp = temp->next;
	}
	Entry * newEntry = malloc(sizeof(Entry));
	newEntry->number = number;
    newEntry->count = 1;
    if (1 == hash->frequency) {
        hash->count++;
    }
    newEntry->next = (hash->base)[index]->next;
	(hash->base)[index]->next = newEntry;
}
int recursiveFindFrequentTreeSum(Hash * hash, struct TreeNode * node) {
    if (node == NULL) {
        return 0;
    }
    int left, right, sum;
    left = recursiveFindFrequentTreeSum(hash, node->left);
    right = recursiveFindFrequentTreeSum(hash, node->right);
    sum = left + right + node->val;
    hashInsert(hash, sum);
    return sum;
}
int* findFrequentTreeSum(struct TreeNode* root, int* returnSize) {
    Hash * hash = createHash(1001);
    recursiveFindFrequentTreeSum(hash, root);
    *returnSize = hash->count;
    int * result = malloc(sizeof(int) * hash->count);
    int index;
    int number = 0;
    for (index = 0 ; index < hash->bounds ; ++index) {
        Entry * temp = (hash->base)[index]->next;
    	while(temp) {
    		if (temp->count == hash->frequency) {
                result[number++] = temp->number;
            }
    		temp = temp->next;
    	}
    }
    return result;
}


















































