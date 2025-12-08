/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverse(struct ListNode* curr) {
    if (!curr || !curr->next) return curr;

    struct ListNode* ret = reverse(curr->next);
    struct ListNode* next = curr->next;
    next->next = curr;
    curr->next = NULL;
    return ret;
}
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    int cnt = 0;
    struct ListNode* prev = NULL;
    struct ListNode* next = NULL;
    struct ListNode* start = NULL;
    struct ListNode* end = NULL;
    for (struct ListNode* curr = head; curr; curr = curr->next) {
        cnt++;
        if (cnt == left - 1) prev = curr;
        if (cnt == left) start = curr;
        if (cnt == right) end = curr;
        if (cnt == right + 1) next = curr;
    }

    end->next = NULL;
    if (prev)
        prev->next = reverse(start);
    else
        head = reverse(start);
    start->next = next;
    return head;
}