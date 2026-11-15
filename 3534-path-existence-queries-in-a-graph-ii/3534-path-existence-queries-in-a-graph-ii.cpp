
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        vector<pair<int, int>> arr(n);

        for (int i = 0; i < n; i++)
            arr[i] = {nums[i], i};

        sort(arr.begin(), arr.end());

        vector<int> pos(n);
        vector<int> values(n);

        for (int i = 0; i < n; i++) {
            values[i] = arr[i].first;
            pos[arr[i].second] = i;
        }

        const int LOG = 18;
        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++) {
            up[0][i] = upper_bound(values.begin(), values.end(),
                                   values[i] + maxDiff) - values.begin() - 1;
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto& q : queries) {
            int u = pos[q[0]];
            int v = pos[q[1]];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            if (u > v) swap(u, v);

            if (values[v] - values[u] > 1LL * maxDiff * n) {
                ans.push_back(-1);
                continue;
            }

            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][u] < v) {
                    u = up[k][u];
                    steps += (1 << k);
                }
            }

            if (up[0][u] >= v)
                ans.push_back(steps + 1);
            else
                ans.push_back(-1);
        }

        return ans;
    }
};
