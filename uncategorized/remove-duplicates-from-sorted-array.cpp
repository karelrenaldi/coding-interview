// Problem link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/

#include <iostream>
#include <vector>

class Solution {
    public:
        // Time complexity: O(N), Space Complexity: O(N).
        int removeDuplicates(std::vector<int>& nums) {
            std::vector<int> new_nums;
            new_nums.push_back(nums[0]);

            int k = 1, curr_num = nums[0];
            for(int i = 1; i < nums.size(); i++) {
                if(curr_num != nums[i]) {
                    new_nums.push_back(nums[i]);

                    curr_num = nums[i];
                    k++;
                }
            }
            nums = new_nums;

            return k;
        }
};

class Solution2 {
    public:
        // Time complexity: O(N), Space Complexity: O(1)
        int removeDuplicates(std::vector<int>& nums) {
            int j = 1, k = 1;
            for(int i = 1; i < nums.size(); i++) {
                if(nums[i] != nums[i - 1]) {
                    nums[j++] = nums[i];
                    k++;
                }
            }

            return k;
        }
};