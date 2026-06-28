/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#define debug(x) printf("%s is %d\n", #x, x);
typedef struct ListNode listNode;
listNode* reverse(listNode* head, int k) {
    listNode* prev = NULL;
    for (listNode* curr = head, *next; k > 0; k--, curr = next) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }
    return prev;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    int cnt = 0;
    listNode* curr;
    for (curr = head; cnt < k && curr; curr = curr->next)
        cnt++;

    if (cnt == k) {
        listNode* reversedHead = reverse(head, k);
        head->next = reverseKGroup(curr, k);
        return reversedHead;
    }
    return head;
}