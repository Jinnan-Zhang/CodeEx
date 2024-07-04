// * Q: https://leetcode.cn/problems/merge-k-sorted-lists/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* detectCycle(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    ListNode *p1 = head, *p2 = head;
    while (p2 != nullptr && p2->next != nullptr) {
        p1 = p1->next;
        p2 = p2->next->next;
        if (p1 == p2) {  // k and 2k steps
            break;
        }
    }
    // no loop
    if (p2 == nullptr || p2->next == nullptr) {
        return nullptr;
    }
    p2 = head;
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

int LinkedListCycleII() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    vector<ListNode*> ln = {l1, l2};
    ListNode* l3 = detectCycle(l1);
    while (l3 != nullptr) {
        cout << l3->val << endl;
        l3 = l3->next;
    }
    return 0;
}