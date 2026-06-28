/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#define debug(x) printf("%s is %d\n", #x, x);
typedef struct ListNode list;
list* reverse(list* head, int k) {
    list* prev = NULL;
    for (list* curr = head, *next; k--; curr = next) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
    }
    return prev;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    list* curr;
    int cnt;
    for (curr = head; cnt < k && curr; curr = curr->next)
        cnt++;

    if (cnt == k) {
        list* rev_head = reverse(head, k);
        head->next = reverseKGroup(curr, k);
        return rev_head;
    }

    return head;
}