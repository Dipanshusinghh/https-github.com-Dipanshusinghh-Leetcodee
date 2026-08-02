class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        // dp[l][r] = maximum score difference current player can achieve
        // from piles[l...r]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // Base Case: Agar sirf ek pile bachi hai
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }
        // Length of subarray
        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                // Left ya Right pile choose karo
                int takeLeft = piles[l] - dp[l + 1][r];
                int takeRight = piles[r] - dp[l][r - 1];
                dp[l][r] = max(takeLeft, takeRight);
            }
        }
        return dp[0][n - 1] > 0;
    }
};