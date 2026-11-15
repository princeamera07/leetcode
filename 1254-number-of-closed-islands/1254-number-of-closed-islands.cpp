
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int ans = 0;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        function<bool(int, int)> dfs = [&](int r, int c) {
            if (r < 0 || c < 0 || r >= m || c >= n)
                return false;

            if (grid[r][c] == 1)
                return true;

            grid[r][c] = 1;
            bool closed = true;

            for (int d = 0; d < 4; d++) {
                closed &= dfs(r + dx[d], c + dy[d]);
            }

            return closed;
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    if (dfs(i, j))
                        ans++;
                }
            }
        }

        return ans;
    }
};
