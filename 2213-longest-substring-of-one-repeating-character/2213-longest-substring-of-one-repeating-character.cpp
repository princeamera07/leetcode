
class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size();

        map<int, int> segments;
        multiset<int> lengths;

        auto add = [&](int l, int r) {
            if (l <= r) {
                segments[l] = r;
                lengths.insert(r - l + 1);
            }
        };

        auto remove = [&](int l) {
            int r = segments[l];
            lengths.erase(lengths.find(r - l + 1));
            segments.erase(l);
        };

        int start = 0;
        for (int i = 1; i <= n; i++) {
            if (i == n || s[i] != s[start]) {
                add(start, i - 1);
                start = i;
            }
        }

        vector<int> ans;

        for (int q = 0; q < queryIndices.size(); q++) {
            int idx = queryIndices[q];
            char ch = queryCharacters[q];

            if (s[idx] != ch) {
                auto it = segments.upper_bound(idx);
                --it;

                int l = it->first;
                int r = it->second;

                remove(l);

                add(l, idx - 1);
                add(idx + 1, r);

                s[idx] = ch;

                int newL = idx;
                int newR = idx;

                auto right = segments.lower_bound(idx);

                if (right != segments.begin()) {
                    auto left = prev(right);

                    if (left->second == idx - 1 &&
                        s[idx - 1] == ch) {
                        newL = left->first;
                        remove(left->first);
                    }
                }

                right = segments.lower_bound(idx + 1);

                if (right != segments.end() &&
                    right->first == idx + 1 &&
                    s[idx + 1] == ch) {
                    newR = right->second;
                    remove(right->first);
                }

                add(newL, newR);
            }

            ans.push_back(*lengths.rbegin());
        }

        return ans;
    }
};
