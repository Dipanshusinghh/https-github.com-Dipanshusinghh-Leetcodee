#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
class Solution {
    const int MOD = 1e9 + 7;
    typedef long long ll;
    // Helper function to calculate (base^exp) % MOD using Binary Exponentiation
    ll power(ll base, ll exp) {
        ll res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }
    // Modular Inverse using Fermat's Little Theorem
    ll modInverse(ll n) {
        return power(n, MOD - 2);
    }
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int sqrtN = sqrt(n);
        // Groups stores queries where the 'step' (k) is small.
        // smallStepQueries[step] = list of {start, end, multiplier}
        vector<vector<vector<int>>> smallStepQueries(sqrtN + 1);
        for (const auto& query : queries) {
            int left = query[0], right = query[1], step = query[2], val = query[3];
            if (step >= sqrtN) {
                // BRUTE FORCE for Large Steps: 
                // If step is large, there are very few elements to update (less than sqrt(N)).
                for (int i = left; i <= right; i += step) {
                    nums[i] = (1LL * nums[i] * val) % MOD;
                }
            } else {
                // DEFER for Small Steps:
                // If step is small, we group them to process efficiently later.
                smallStepQueries[step].push_back({left, right, val});
            }
        }
        // Process Small Step Queries using a "Difference Array" technique
        for (int step = 1; step < sqrtN; step++) {
            if (smallStepQueries[step].empty()) continue;
            // diff[i] stores the multiplier effect for index i
            vector<ll> diff(n + step + 1, 1); 
            for (const auto& q : smallStepQueries[step]) {
                int l = q[0], r = q[1], v = q[2];
                // Multiply start by v
                diff[l] = (diff[l] * v) % MOD;   
                // To stop the effect after the range, multiply the next 
                // element in the sequence (r + step) by the modular inverse of v
                int lastIndex = ((r - l) / step + 1) * step + l;
                if (lastIndex < diff.size()) {
                    diff[lastIndex] = (diff[lastIndex] * modInverse(v)) % MOD;
                }
            }
            // Prefix product: Carry the multiplier forward with the given 'step'
            for (int i = step; i < n; i++) {
                diff[i] = (diff[i] * diff[i - step]) % MOD;
            }
            // Apply the calculated multipliers to the original nums array
            for (int i = 0; i < n; i++) {
                nums[i] = (1LL * nums[i] * diff[i]) % MOD;
            }
        }
        // Final result: XOR of all modified elements
        int result = 0;
        for (int val : nums) {
            result ^= val;
        }
        return result;
    }
};