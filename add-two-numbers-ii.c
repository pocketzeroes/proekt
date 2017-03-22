typedef struct ListNode ListNode ;
// * struct ListNode {
// *     int val;
// *     struct ListNode *next;
// * };
ListNode*newListNode(int v){
    ListNode*rez=malloc(sizeof(ListNode));
    rez->val=v;
    rez->next=NULL;
    return rez;
}
    ListNode* addToFront( int val, ListNode* head ){
        ListNode* temp = newListNode(val);
        temp->next = head;
        return temp;
    }
 ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int n1 = 0, n2 = 0, carry = 0;
        ListNode *curr1 = l1, *curr2 = l2, *res = NULL;
        while( curr1 ){ curr1=curr1->next; n1++; }
        while( curr2 ){ curr2=curr2->next; n2++; } 
        curr1 = l1; curr2 = l2;
        while( n1 > 0 && n2 > 0){
            int sum = 0;
            if( n1 >= n2 ){ sum += curr1->val; curr1=curr1->next; n1--;}
            if( n2 > n1 ){ sum += curr2->val; curr2=curr2->next; n2--;}
            res = addToFront( sum, res );
        }
        curr1 = res; res = NULL;
        while( curr1 ){
            curr1->val += carry; carry = curr1->val/10;
            res = addToFront( curr1->val%10, res );
            curr2 = curr1; 
            curr1 = curr1->next;
//            delete curr2;
        }
        if( carry ) res = addToFront( 1, res );
        return res;
    }
