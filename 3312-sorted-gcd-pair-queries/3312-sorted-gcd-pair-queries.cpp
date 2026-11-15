
class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums)
            freq[x]++;

        vector<long long> cnt(mx + 1, 0);

        for (int g = 1; g <= mx; g++) {
            long long total = 0;

            for (int j = g; j <= mx; j += g)
                total += freq[j];

            cnt[g] = total * (total - 1) / 2;
        }

        for (int g = mx; g >= 1; g--) {
            for (int j = 2 * g; j <= mx; j += g)
                cnt[g] -= cnt[j];
        }

        vector<long long> prefix(mx + 1, 0);

        for (int g = 1; g <= mx; g++)
            prefix[g] = prefix[g - 1] + cnt[g];

        vector<int> answer;

        for (long long q : queries) {
            int l = 1, r = mx;

            while (l < r) {
                int mid = l + (r - l) / 2;

                if (prefix[mid] > q)
                    r = mid;
                else
                    l = mid + 1;
            }

            answer.push_back(l);
        }

        return answer;
    }
};
