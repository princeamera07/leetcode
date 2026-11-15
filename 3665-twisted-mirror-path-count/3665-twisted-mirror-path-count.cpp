
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // memo[direction][row * n + col]
        // direction: 0 = right, 1 = down
        vector<vector<int>> memo(2, vector<int>(m * n, -2));

        function<int(int, int, int)> solve =
            [&](int r, int c, int dir) -> int {

            if (r >= m || c >= n)
                return -1;

            int id = r * n + c;

            if (memo[dir][id] != -2)
                return memo[dir][id];

            if (grid[r][c] == 0)
                return memo[dir][id] = id;

            int nr = r, nc = c, ndir = dir;

            if (dir == 0) {
                nr++;
                ndir = 1;
            } else {
                nc++;
                ndir = 0;
            }

            return memo[dir][id] = solve(nr, nc, ndir);
        };

        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                // Try moving right
                int right = solve(i, j + 1, 0);

                if (right != -1) {
                    int r = right / n;
                    int c = right % n;

                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                }

                // Try moving down
                int down = solve(i + 1, j, 1);

                if (down != -1) {
                    int r = down / n;
                    int c = down % n;

                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};
