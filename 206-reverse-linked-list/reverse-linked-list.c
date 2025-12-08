/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* curr = head;
    if (!curr) return NULL;
    struct ListNode* next = head->next;
    if (!next) return curr;
    
    struct ListNode* ret = reverseList(next);
    next->next = curr;
    curr->next = NULL;

    return ret;
}