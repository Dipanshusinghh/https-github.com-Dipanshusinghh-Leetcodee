class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<long long> st;
        // store obstacles
        for (auto &o : obstacles) {
            long long key = ((long long)o[0] << 32) | (o[1] & 0xffffffff);
            st.insert(key);
        }
        // directions: N, E, S, W
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int d = 0;
        int x = 0, y = 0;
        int ans = 0;
        for (int cmd : commands) {
            if (cmd == -1) {
                d = (d + 1) % 4;
            } 
            else if (cmd == -2) {
                d = (d + 3) % 4;
            } 
            else {
                for (int step = 0; step < cmd; step++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    long long key = ((long long)nx << 32) | (ny & 0xffffffff);
                    if (st.count(key)) break;
                    x = nx;
                    y = ny;
                    ans = max(ans, x*x + y*y);
                }
            }
        }
        return ans;
    }
};