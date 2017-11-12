typedef struct ListNode ListNode;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ListNode* *pushback(ListNode* *array, int *size, ListNode* value) {
    ListNode* *output = resizeArray(array, ListNode*, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct{
	ListNode**ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int len(ListNode*x){
    int ret = 0;
    while(x)
        x = x->next, ret++;
    return ret;
}
ListNode**splitListToParts(ListNode*root, int k, int*rsz){
    int l = len(root);
    vec ret = newVec();
    for (int i = 0; i < k; ++i){
        if (root == NULL){
            ret.ptr = pushback(ret.ptr, &ret.sz, NULL);
            continue;
        }
        int t = (l / k) + (i < (l % k));
        ret.ptr = pushback(ret.ptr, &ret.sz, root);
        for (int i = 0; i < t - 1; ++i)
            root = root->next;
        ListNode *tmp = root->next;
        root->next = NULL;
        root = tmp;
    }
   *rsz=   ret.sz;
    return ret.ptr;
}
