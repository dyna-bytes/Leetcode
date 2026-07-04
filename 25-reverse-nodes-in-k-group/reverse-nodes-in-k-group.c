/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverse(struct ListNode* head, int k) {
    struct ListNode* prev = NULL;
    for (struct ListNode* curr = head, *next; k; k--, curr = next) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }

    return prev;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    int cnt = 0;
    struct ListNode* ret = NULL, *curr;
    for (curr = head; cnt < k && curr; curr = curr->next) 
        cnt++;
    
    if (cnt == k) {
        struct ListNode* rev_head = reverse(head, k);
        head->next = reverseKGroup(curr, k);
        return rev_head;
    }
    return head;
}