#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size();
    int sum = numbers[left] + numbers[right];
    while (left < right) {
        if (sum == target) {
            return {left, right};
        }
    }
}

int main() {
    vector<int> nums = {1, 2, 3, 4};
    cout << twoSum(nums, 5)[0] << endl;
    cout << twoSum(nums, 5)[1] << endl;
    return 0;
}