
class Solution {
public:
    void fwht(vector<long long>& a, bool inverse) {
        int n = a.size();

        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    long long u = a[i + j];
                    long long v = a[i + j + len];

                    a[i + j] = u + v;
                    a[i + j + len] = u - v;
                }
            }
        }

        if (inverse) {
            for (auto& x : a) x /= n;
        }
    }

    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        const int SZ = 2048;

        vector<long long> freq(SZ, 0);

        for (int x : nums) {
            freq[x]++;
        }

        vector<long long> f = freq;

        fwht(f, false);

        for (auto& x : f) {
            x = x * x * x;
        }

        fwht(f, true);

        int ans = 0;

        for (int x = 0; x < SZ; x++) {
            long long distinctTriplets =
                f[x] - (3LL * n - 2) * freq[x];

            if (distinctTriplets > 0 || freq[x] > 0) {
                ans++;
            }
        }

        return ans;
    }
};
