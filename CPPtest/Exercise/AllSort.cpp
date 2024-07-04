#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<vector<int>> result;

    return result;
}

void backtrack(int first, int length, vector<int> input, vector<int> output, vector<bool> vis, vector<vector<int>> &result) {
    if (first == length) {
        result.push_back(output);
        return;
    } else {
        for (int i = 0; i < length; i++) {
            if (!vis[i]) {
                output[first] = input[i];
                vis[i] = true;
                // 移到下一位
                backtrack(first + 1, length, input, output, vis, result);
                // 为什么要复位？回溯用的
                vis[i] = false;
            }
        }
    }
}

vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> result;
    int n = nums.size();
    vector<int> output(n, 0);
    vector<bool> vis(n, false);
    backtrack(0, n, nums, output, vis, result);

    return result;
}

int AllSort() {
    vector<int> nums = {1, 3, 2};
    // vector<vector<int>> result = permuteUnique(nums);
    vector<vector<int>> result = permute(nums);
    for (auto iter : result) {
        for (auto jter : iter) {
            cout << jter << ", ";
        }
        cout << endl;
    }
    return 0;
}
