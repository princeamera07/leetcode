
class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAXG = 200;

        vector<vector<int>> dp(MAXG + 1, vector<int>(MAXG + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp(MAXG + 1, vector<int>(MAXG + 1, 0));

            for (int g1 = 0; g1 <= MAXG; g1++) {
                for (int g2 = 0; g2 <= MAXG; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    int ways = dp[g1][g2];

                    // Do not include the current element
                    ndp[g1][g2] = (ndp[g1][g2] + ways) % MOD;

                    // Include in the first subsequence
                    int ng1 = gcd(g1, x);
                    ndp[ng1][g2] = (ndp[ng1][g2] + ways) % MOD;

                    // Include in the second subsequence
                    int ng2 = gcd(g2, x);
                    ndp[g1][ng2] = (ndp[g1][ng2] + ways) % MOD;
                }
            }

            dp = move(ndp);
        }

        int ans = 0;

        for (int g = 1; g <= MAXG; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};
