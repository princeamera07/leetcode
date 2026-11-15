
class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();

        sort(word.begin(), word.end());

        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans += (i / 8 + 1);
        }

        return ans;
    }
};
