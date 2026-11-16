
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> ans;
        vector<int> curr;

        function<void(int, int)> backtrack = [&](int start, int sum) {
            if (sum == target) {
                ans.push_back(curr);
                return;
            }

            for (int i = start; i < candidates.size(); i++) {
                if (i > start && candidates[i] == candidates[i - 1])
                    continue;

                if (sum + candidates[i] > target)
                    break;

                curr.push_back(candidates[i]);
                backtrack(i + 1, sum + candidates[i]);
                curr.pop_back();
            }
        };

        backtrack(0, 0);
        return ans;
    }
};
