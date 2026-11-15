
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        int sr = 0, sc = 0, k = 0;

        vector<vector<int>> litter(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    litter[i][j] = k++;
                }
            }
        }

        if (k == 0) return 0;

        int totalMasks = 1 << k;
        int target = totalMasks - 1;

        int totalStates = m * n * totalMasks * (energy + 1);
        vector<bool> visited(totalStates, false);

        auto getId = [&](int r, int c, int mask, int e) {
            return (((r * n + c) * totalMasks + mask) * (energy + 1) + e);
        };

        queue<tuple<int, int, int, int, int>> q;

        q.push({sr, sc, 0, energy, 0});
        visited[getId(sr, sc, 0, energy)] = true;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, mask, e, steps] = q.front();
            q.pop();

            if (mask == target) return steps;

            if (e == 0) continue;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                if (classroom[nr][nc] == 'X') continue;

                int newMask = mask;
                int newEnergy = e - 1;

                if (litter[nr][nc] != -1)
                    newMask |= (1 << litter[nr][nc]);

                if (classroom[nr][nc] == 'R')
                    newEnergy = energy;

                int id = getId(nr, nc, newMask, newEnergy);

                if (!visited[id]) {
                    visited[id] = true;
                    q.push({nr, nc, newMask, newEnergy, steps + 1});
                }
            }
        }

        return -1;
    }
};
