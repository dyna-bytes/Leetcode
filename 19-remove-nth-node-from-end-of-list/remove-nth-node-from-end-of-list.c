/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* fast = head;
    for (; fast && n; fast = fast->next)
        n--;
    
    struct ListNode** slow = &head;
    for (; fast; fast = fast->next)
        slow = &(*slow)->next;

    (*slow) = (*slow)->next;
    return head;
}