
class Solution {
    vector<vector<int>> adj, up;
    vector<int> depth, tin, tout, bit, fenwick;
    int timer, LOG;

    void add(int i, int val) {
        for (i++; i < (int)fenwick.size(); i += i & -i)
            fenwick[i] ^= val;
    }

    int sum(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i)
            res ^= fenwick[i];
        return res;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++)
            if (diff & (1 << j))
                u = up[j][u];

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(LOG, vector<int>(n, 0));
        depth.assign(n, 0);
        tin.resize(n);
        tout.resize(n);
        bit.resize(n);

        for (int i = 0; i < n; i++)
            bit[i] = 1 << (s[i] - 'a');

        timer = 0;

        // Iterative Euler tour to avoid recursion stack overflow.
        vector<tuple<int, int, int>> st;
        st.push_back({0, 0, 0});

        while (!st.empty()) {
            auto [u, p, state] = st.back();
            st.pop_back();

            if (state == 0) {
                tin[u] = timer++;
                up[0][u] = p;

                for (int j = 1; j < LOG; j++)
                    up[j][u] = up[j - 1][up[j - 1][u]];

                st.push_back({u, p, 1});

                for (int v : adj[u]) {
                    if (v == p) continue;
                    depth[v] = depth[u] + 1;
                    st.push_back({v, u, 0});
                }
            } else {
                tout[u] = timer++;
            }
        }

        fenwick.assign(timer + 1, 0);

        for (int u = 0; u < n; u++) {
            add(tin[u], bit[u]);
            add(tout[u], bit[u]);
        }

        vector<bool> ans;

        for (string& q : queries) {
            string op;
            int u;
            string b;

            stringstream ss(q);
            ss >> op >> u >> b;

            if (op == "update") {
                int newBit = 1 << (b[0] - 'a');
                int delta = bit[u] ^ newBit;

                if (delta) {
                    add(tin[u], delta);
                    add(tout[u], delta);
                    bit[u] = newBit;
                }
            } else {
                int v = stoi(b);
                int w = lca(u, v);

                int mask = sum(tin[u] + 1)
                         ^ sum(tin[v] + 1)
                         ^ bit[w];

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
