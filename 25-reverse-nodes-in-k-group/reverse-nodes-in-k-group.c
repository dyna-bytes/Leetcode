/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode listNode;

// reverse list from head to size k. return reversed head.
listNode* reverse(listNode* head, int k) {
    listNode* curr = head;
    listNode* prev = NULL;
    listNode* next = NULL;
    for (; curr && k > 0; k--, curr = next) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }
    return prev;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    listNode* curr = head;
    int i = 0;
    for (; curr && i < k; i++, curr = curr->next);

    if (i == k) {
        listNode* rev_head = reverse(head, k);
        head->next = reverseKGroup(curr, k);
        return rev_head;
    }
    return head;
}