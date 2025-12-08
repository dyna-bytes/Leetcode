/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* stck[1 << 13];
    int sp = 0;

    for (struct ListNode* curr = head; curr; curr = curr->next)     
        stck[++sp] = curr;

    struct ListNode* prev = NULL;
    while (sp > 0) {
        struct ListNode* curr = stck[sp--];
        if (prev)
            prev->next = curr;
        else 
            head = curr;
        
        prev = curr;
        curr->next = NULL;
    }

    return head;
}