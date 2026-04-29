using ll = long long;

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Prefix sum for each column
        vector<vector<ll>> colSum(n, vector<ll>(n + 1, 0));
        for (int c = 0; c < n; c++) {
            for (int r = 1; r <= n; r++) {
                colSum[c][r] = colSum[c][r - 1] + grid[r - 1][c];
            }
        }

        // Only keep previous and current DP
        vector<vector<ll>> prevDP(n + 1, vector<ll>(n + 1, 0));
        vector<vector<ll>> currDP(n + 1, vector<ll>(n + 1, 0));

        vector<vector<ll>> prevMax(n + 1, vector<ll>(n + 1, 0));
        vector<vector<ll>> prevSuffixMax(n + 1, vector<ll>(n + 1, 0));

        for (int col = 1; col < n; col++) {

            // reset current DP
            for (int i = 0; i <= n; i++)
                fill(currDP[i].begin(), currDP[i].end(), 0);

            for (int currH = 0; currH <= n; currH++) {
                for (int prevH = 0; prevH <= n; prevH++) {

                    if (currH <= prevH) {
                        ll gain = colSum[col][prevH] - colSum[col][currH];

                        currDP[currH][prevH] =
                            prevSuffixMax[prevH][0] + gain;
                    }
                    else {
                        ll gain = colSum[col - 1][currH] - colSum[col - 1][prevH];

                        currDP[currH][prevH] = max({
                            prevSuffixMax[prevH][currH],
                            prevMax[prevH][currH] + gain
                        });
                    }
                }
            }

            // rebuild helpers
            for (int currH = 0; currH <= n; currH++) {

                prevMax[currH][0] = currDP[currH][0];

                for (int prevH = 1; prevH <= n; prevH++) {
                    ll penalty = (prevH > currH)
                        ? (colSum[col][prevH] - colSum[col][currH])
                        : 0;

                    prevMax[currH][prevH] = max(
                        prevMax[currH][prevH - 1],
                        currDP[currH][prevH] - penalty
                    );
                }

                prevSuffixMax[currH][n] = currDP[currH][n];

                for (int prevH = n - 1; prevH >= 0; prevH--) {
                    prevSuffixMax[currH][prevH] = max(
                        prevSuffixMax[currH][prevH + 1],
                        currDP[currH][prevH]
                    );
                }
            }

            // move current → previous
            prevDP = currDP;
        }

        ll ans = 0;
        for (int k = 0; k <= n; k++) {
            ans = max({ans, prevDP[n][k], prevDP[0][k]});
        }

        return ans;
    }
};