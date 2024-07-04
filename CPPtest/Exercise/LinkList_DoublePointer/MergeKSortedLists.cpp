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

struct Cmp {
    bool operator()(ListNode* l1, ListNode* l2) {
        return l1->val > l2->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode *result = new ListNode(), *p = result;
    priority_queue<ListNode*, vector<ListNode*>, Cmp> allLists;
    ListNode* temp;
    for (int i = 0; i < lists.size(); i++) {
        while (lists[i] != nullptr) {
            allLists.push(lists[i]);
            temp = lists[i]->next;
            lists[i]->next = nullptr;
            lists[i] = temp;
        }
    }
    while (!allLists.empty()) {
        p->next = allLists.top();
        allLists.pop();
        p = p->next;
    }

    return result->next;
}

// ListNode* mergeKLists(vector<ListNode*>& lists) {
//     ListNode *result = new ListNode(), *p = result;
//     priority_queue<ListNode*, vector<ListNode*>, Cmp> allLists;
//     for (auto i : lists) {
//         if (i != nullptr) {
//             allLists.push(i);
//         }
//     }
//     ListNode* temp;
//     while (!allLists.empty()) {
//         temp = allLists.top();
//         allLists.pop();
//         p->next = temp;
//         p = p->next;
//         if (temp->next != nullptr) {
//             allLists.push(temp->next);
//         }
//     }

//     return result->next;
// }

int MergeKSortedLists() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    vector<ListNode*> ln = {l1, l2};
    ListNode* l3 = mergeKLists(ln);
    while (l3 != nullptr) {
        cout << l3->val << endl;
        l3 = l3->next;
    }
    return 0;
}