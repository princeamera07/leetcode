
class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1e9 + 7;
        int n = s.size();

        vector<long long> prefixValue(n + 1, 0);
        vector<long long> prefixSum(n + 1, 0);
        vector<int> prefixCount(n + 1, 0);
        vector<long long> power10(n + 1, 1);

        for (int i = 0; i < n; i++) {
            power10[i + 1] = (power10[i] * 10) % MOD;

            prefixValue[i + 1] = prefixValue[i];
            prefixSum[i + 1] = prefixSum[i];
            prefixCount[i + 1] = prefixCount[i];

            int digit = s[i] - '0';

            if (digit != 0) {
                prefixValue[i + 1] = (prefixValue[i] * 10 + digit) % MOD;
                prefixSum[i + 1] += digit;
                prefixCount[i + 1]++;
            }
        }

        vector<int> answer;

        for (auto& q : queries) {
            int l = q[0], r = q[1];

            int count = prefixCount[r + 1] - prefixCount[l];
            long long sum = prefixSum[r + 1] - prefixSum[l];

            long long x = (prefixValue[r + 1] -
                prefixValue[l] * power10[count] % MOD + MOD) % MOD;

            answer.push_back((x * sum) % MOD);
        }

        return answer;
    }
};
