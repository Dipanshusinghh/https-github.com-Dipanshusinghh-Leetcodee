class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& pos, vector<int>& health, string dir) {
        int n = pos.size();        
        // Store {position, index}
        vector<pair<int,int>> robots;
        for(int i = 0; i < n; i++) {
            robots.push_back({pos[i], i});
        }
        // Sort by position
        sort(robots.begin(), robots.end());
        stack<int> st; // stores indices of robots
        vector<int> h = health; // copy of health
        for(auto &r : robots) {
            int i = r.second;
            if(dir[i] == 'R') {
                st.push(i);
            } 
            else {
                // Collision with previous R robots
                while(!st.empty() && h[i] > 0) {
                    int j = st.top();
                    st.pop();
                    if(h[j] > h[i]) {
                        h[j]--;
                        h[i] = 0;
                        st.push(j);
                    } 
                    else if(h[j] < h[i]) {
                        h[i]--;
                        h[j] = 0;
                    } 
                    else {
                        h[i] = 0;
                        h[j] = 0;
                    }
                }
            }
        }
        // Collect survivors
        vector<int> res;
        for(int i = 0; i < n; i++) {
            if(h[i] > 0) res.push_back(h[i]);
        }
        return res;
    }
};