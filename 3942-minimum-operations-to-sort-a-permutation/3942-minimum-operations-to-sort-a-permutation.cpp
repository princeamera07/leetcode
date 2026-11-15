
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        vector<int> target(n);

        for (int i = 0; i < n; i++)
            target[i] = i;

        vector<vector<int>> dist(2, vector<int>(n, -1));
        queue<pair<int, int>> q;

        dist[0][0] = 0;
        q.push({0, 0});

        int pos1 = find(nums.begin(), nums.end(), 0) - nums.begin();

        vector<int> rev = nums;
        reverse(rev.begin(), rev.end());

        int pos2 = find(rev.begin(), rev.end(), 0) - rev.begin();

        while (!q.empty()) {
            auto [type, shift] = q.front();
            q.pop();

            int d = dist[type][shift];
            vector<int>& arr = (type == 0 ? nums : rev);

            bool valid = true;
            for (int i = 0; i < n; i++) {
                if (arr[(i + shift) % n] != i) {
                    valid = false;
                    break;
                }
            }

            if (valid) return d;

            int nextShift = (shift + 1) % n;

            if (dist[type][nextShift] == -1) {
                dist[type][nextShift] = d + 1;
                q.push({type, nextShift});
            }

            int reverseShift = (n - shift) % n;

            if (dist[1 - type][reverseShift] == -1) {
                dist[1 - type][reverseShift] = d + 1;
                q.push({1 - type, reverseShift});
            }
        }

        return -1;
    }
};
