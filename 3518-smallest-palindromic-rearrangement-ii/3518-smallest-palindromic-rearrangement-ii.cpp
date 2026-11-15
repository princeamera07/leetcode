
class Solution {
public:
    long long comb(int n, int r, long long limit) {
        r = min(r, n - r);
        __int128 res = 1;

        for (int i = 1; i <= r; i++) {
            res = res * (n - r + i) / i;
            if (res > limit) return limit + 1;
        }

        return (long long)res;
    }

    long long countWays(vector<int>& freq, long long limit) {
        int total = 0;
        long long ways = 1;

        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) continue;

            long long c = comb(total + freq[i], freq[i], limit);

            __int128 product = (__int128)ways * c;
            ways = product > limit ? limit + 1 : (long long)product;

            total += freq[i];

            if (ways > limit) return limit + 1;
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        string half;
        char middle = '\0';

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) middle = 'a' + i;

            freq[i] /= 2;
            half += string(freq[i], 'a' + i);
        }

        vector<int> remaining = freq;

        if (countWays(remaining, k) < k) return "";

        string left;

        while (!half.empty()) {
            for (int i = 0; i < 26; i++) {
                if (remaining[i] == 0) continue;

                remaining[i]--;

                long long ways = countWays(remaining, k);

                if (ways >= k) {
                    left += char('a' + i);
                    half.pop_back();
                    break;
                }

                k -= ways;
                remaining[i]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (middle != '\0') left += middle;

        return left + right;
    }
};
