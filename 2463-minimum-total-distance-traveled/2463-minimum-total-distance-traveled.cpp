class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        int n = robot.size();
        int m = factory.size();
        // Memoization table: memo[robot_idx][factory_idx]
        vector<vector<long long>> memo(n, vector<long long>(m, -1));   
        return solve(0, 0, robot, factory, memo);
    }
    long long solve(int rIdx, int fIdx, vector<int>& robot, vector<vector<int>>& factory, vector<vector<long long>>& memo) {
        // Base Case: All robots are assigned
        if (rIdx == robot.size()) return 0;
        // Base Case: No more factories left, but robots remain
        if (fIdx == factory.size()) return 1e15; // Use a sufficiently large value
        if (memo[rIdx][fIdx] != -1) return memo[rIdx][fIdx];
        // Option 1: Skip the current factory entirely
        long long res = solve(rIdx, fIdx + 1, robot, factory, memo);
        // Option 2: Assign 'k' robots to the current factory
        long long current_dist = 0;
        for (int k = 0; k < factory[fIdx][1] && rIdx + k < robot.size(); ++k) {
            current_dist += abs(robot[rIdx + k] - factory[fIdx][0]);   
            long long next_dist = solve(rIdx + k + 1, fIdx + 1, robot, factory, memo);
            if (next_dist != 1e15) {
                res = min(res, current_dist + next_dist);
            }
        }
        return memo[rIdx][fIdx] = res;
    }
};