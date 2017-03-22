struct Node {
    int count;
    long long val;
    struct Node *left, *right;
};

void insert(struct Node *r, long long v, long long diff) {
    r->count++;
    if (r->val == v) return;
    if (v > r->val) {
        if (!r->right) {
            r->right = (struct Node *)malloc(sizeof(struct Node));
            r->right->count = 0;
            r->right->left = 0;
            r->right->right = 0;
            r->right->val = r->val + diff;
        }
        insert(r->right, v, diff / 2);
    } else {
        if (!r->left) {
            r->left = (struct Node *)malloc(sizeof(struct Node));
            r->left->count = 0;
            r->left->left = 0;
            r->left->right = 0;
            r->left->val = r->val - diff;
        }
        insert(r->left, v, diff / 2);
    }
}

int countLess(struct Node *r, int v) {
  if (!r) return 0;
  int lc = r->left ? r->left->count : 0;
  int rc = r->right ? r->right->count : 0;
  if (r->val < v) return (r->count - lc - rc) + (r->left ? r->left->count : 0) + countLess(r->right, v);
  else return countLess(r->left, v);
}

int reversePairs(int* nums, int numsSize) {
    int count = 0;
    if (numsSize <= 1) return 0;
    struct Node *r = (struct Node *)malloc(sizeof(struct Node));
    r->count = 0;
    r->val = 0;
    r->left = r->right = 0;
    for (int i = numsSize - 1; i>=0; i--) {
        count += countLess(r, nums[i]);
        insert(r,(long long)nums[i] * 2, 1ll << 31);
    }
    return count;
}












