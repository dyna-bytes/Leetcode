/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode listNode;
listNode* mergeTwoLists(listNode* list1, listNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
    return NULL;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    while (listsSize > 1) {
        int newSize = 0;

        for (int i = 0; i < listsSize; i += 2) {
            if (i + 1 < listsSize)
                lists[newSize++] = mergeTwoLists(lists[i], lists[i + 1]);
            else
                lists[newSize++] = lists[i];
        }
        listsSize = newSize;
    }
    return lists[0];
}