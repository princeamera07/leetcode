
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> curr;

        function<void(int, int)> backtrack = [&](int index, int sum) {
            if (sum == target) {
                ans.push_back(curr);
                return;
            }

            if (sum > target || index == candidates.size())
                return;

            curr.push_back(candidates[index]);
            backtrack(index, sum + candidates[index]);

            curr.pop_back();
            backtrack(index + 1, sum);
        };

        backtrack(0, 0);
        return ans;
    }
};
