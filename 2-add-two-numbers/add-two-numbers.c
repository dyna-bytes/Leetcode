/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* add(struct ListNode* l1, struct ListNode* l2, int c) {
    if (!l1 && !l2 && !c) return NULL;

    struct ListNode* ret = calloc(1, sizeof(*ret));
    int x = l1 ? l1->val : 0;
    int y = l2 ? l2->val : 0;
    int z = c;

    z += (x + y);
    c = z / 10;
    z = z % 10;

    struct ListNode* n1 = l1 ? l1->next : NULL;
    struct ListNode* n2 = l2 ? l2->next : NULL;

    ret->val = z;
    ret->next = add(n1, n2, c);
    return ret;
}
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    return add(l1, l2, 0);
}