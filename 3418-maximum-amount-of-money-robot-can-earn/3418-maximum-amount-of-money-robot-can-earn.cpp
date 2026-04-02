class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        // dp[i][j][k] -> max coins from (i,j) with k neutralizations left
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, INT_MIN)));
        // Base case: destination cell
        for (int k = 0; k < 3; k++) {
            if (k > 0)
                dp[m-1][n-1][k] = max(0, coins[m-1][n-1]);
            else
                dp[m-1][n-1][k] = coins[m-1][n-1];
        }
        // Fill DP from bottom-right to top-left
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i == m-1 && j == n-1) continue;
                for (int k = 0; k < 3; k++) {
                    int x = coins[i][j];
                    int best = INT_MIN;
                    // move down
                    if (i + 1 < m)
                        best = max(best, dp[i+1][j][k]);
                    // move right
                    if (j + 1 < n)
                        best = max(best, dp[i][j+1][k]);
                    if (best != INT_MIN)
                        best += x;
                    // neutralize case
                    if (k > 0 && x < 0) {
                        int temp = INT_MIN;
                        if (i + 1 < m)
                            temp = max(temp, dp[i+1][j][k-1]);
                        if (j + 1 < n)
                            temp = max(temp, dp[i][j+1][k-1]);
                        best = max(best, temp);
                    }
                    dp[i][j][k] = best;
                }
            }
        }
        return dp[0][0][2];
    }
};