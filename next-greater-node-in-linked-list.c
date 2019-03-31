typedef struct ListNode ListNode;

int*enumNextWall(int*a, int asz){
    int n = asz;
    int*L = calloc(n, sizeof(int));
    for(int i = n-1;i >= 0;i--){
        L[i] = i+1;
        while(L[i] < n && a[L[i]] <= a[i])
            L[i] = L[L[i]];
    }
    return L;
}
int*nextLargerNodes(ListNode*head, int*rsz){
    int a[10005] = {0};
    int p = 0;
    for(ListNode*x = head; x != NULL; x = x->next){
        a[p++] = x->val;
    }
    int*wa = enumNextWall(a, p);
    for(int i = 0; i < p; i++){
        if(wa[i] == p){
            wa[i] = 0;
        }
        else{
            wa[i] = a[wa[i]];
        }
    }
   *rsz = p;
    return wa;
}
