
class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> freq(51, 0);

        for (int i = 0; i <= n - k; i++) {
            unordered_set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            for (int x : seen) {
                freq[x]++;
            }
        }

        int ans = -1;

        for (int x = 0; x <= 50; x++) {
            if (freq[x] == 1) {
                ans = x;
            }
        }

        return ans;
    }
};
