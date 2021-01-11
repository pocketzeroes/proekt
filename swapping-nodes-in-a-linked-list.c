#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)
typedef struct ListNode ListNode;

ListNode*swapNodes(ListNode*head, int k){
  int n = 0;
  for(ListNode*p = head; p; p = p->next) n += 1;
  ListNode*a = head;
  for(int i = 1; i < k; i += 1) a = a->next;
  ListNode*b = head;
  for(int i = 1; i < n - k + 1; i += 1) b = b->next;
  swap(a->val, b->val);
  return head;
}
