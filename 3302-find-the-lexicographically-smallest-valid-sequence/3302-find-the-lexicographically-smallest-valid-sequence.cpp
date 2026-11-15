
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size(), m = word2.size();

        vector<vector<int>> pos(26);
        for (int i = 0; i < n; i++)
            pos[word1[i] - 'a'].push_back(i);

        auto findPrev = [&](int ch, int bound) {
            auto &v = pos[ch];
            auto it = upper_bound(v.begin(), v.end(), bound);
            if (it == v.begin()) return -1;
            return *prev(it);
        };

        vector<int> exact(m + 1, n - 1);
        vector<int> oneMismatch(m + 1, n - 1);

        for (int j = m - 1; j >= 0; j--) {
            int p = findPrev(word2[j] - 'a', exact[j + 1]);
            exact[j] = p - 1;

            int q = findPrev(word2[j] - 'a', oneMismatch[j + 1]);
            oneMismatch[j] = max(q - 1, exact[j + 1] - 1);
        }

        vector<int> ans;
        int prevIndex = -1;
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {
            bool found = false;

            for (int i = prevIndex + 1; i < n; i++) {
                if (word1[i] == word2[j]) {
                    int limit = usedMismatch ? exact[j + 1] : oneMismatch[j + 1];

                    if (limit >= i) {
                        ans.push_back(i);
                        prevIndex = i;
                        found = true;
                        break;
                    }
                } 
                else if (!usedMismatch && exact[j + 1] >= i) {
                    ans.push_back(i);
                    prevIndex = i;
                    usedMismatch = true;
                    found = true;
                    break;
                }
            }

            if (!found) return {};
        }

        return ans;
    }
};
