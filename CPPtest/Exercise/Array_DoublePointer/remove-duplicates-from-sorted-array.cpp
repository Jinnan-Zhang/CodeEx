// * https://leetcode.cn/problems/remove-duplicates-from-sorted-array/

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

int removeDuplicates(vector<int>& nums) {
    if (nums.size() == 0) {
        return 0;
    }

    int slow = 0;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[slow] != nums[i]) {
            slow++;
            nums[slow] = nums[i];
        }
    }

    return slow + 1;
}

// * Q: https://leetcode.cn/problems/remove-duplicates-from-sorted-list/submissions/
ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr) {
        return head;
    }

    ListNode *slow = head, *fast = head->next;
    while (fast != nullptr) {
        if (slow->val != fast->val) {
            slow->next = fast;
            slow = slow->next;
        }

        fast = fast->next;
    }

    slow->next = nullptr;
    return head;
}

int main() {
    vector<int> nums = {1, 1, 1, 2, 2, 3, 3, 4, 4};
    // cout << removeDuplicates(nums) << endl;

    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    l1->next->next->next = new ListNode(4);
    ListNode* l3 = deleteDuplicates(l1);
    while (l3 != nullptr) {
        cout << l3->val << endl;
        l3 = l3->next;
    }
    return 0;
}