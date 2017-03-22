typedef struct {
    int a;
} Solution;
Solution*ptr;
typedef struct ListNode ListNode ;
ListNode*gHead;
Solution* solutionCreate( ListNode* head) {
    gHead=head;
    return ptr;
}
int solutionGetRandom(Solution* obj) {
        int reservoir = gHead->val;
        int n = 1;
        for (ListNode*curr = gHead->next; curr; curr = curr->next) {
            if (rand() % ++n == 0) {
                reservoir = curr->val;
            }
        }
        return reservoir;
}
void solutionFree(Solution* obj) {
    gHead=NULL;
}
