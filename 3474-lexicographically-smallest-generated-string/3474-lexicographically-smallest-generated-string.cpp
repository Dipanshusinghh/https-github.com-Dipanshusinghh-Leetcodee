class Solution {
public://greedy approch+ string topic  
    string generateString(string str1,string str2) {
        int n = str1.size();
        int m = str2.size();
        // Final result string (initially all 'a')
        string result(n + m - 1, 'a');
        // Marks positions which are already fixed
        vector<bool> isFixed(n + m-1, false);
        // STEP 1: Handle 'T' (True → must match str2)
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    int pos = i+j;
                    // Conflict check
                    if (isFixed[pos] && result[pos] != str2[j]) {
                        return ""; // impossible
                    }
                    // Fix the character
                    result[pos] = str2[j];
                    isFixed[pos] = true;
                }
            }
        }
        // STEP 2: Handle 'F' (False → must NOT match str2)
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {
                bool isDifferent = false;
                int changeIndex = -1;
                for (int j = 0; j < m; j++) {
                    int pos = i+j;
                    // Check if already different
                    if (result[pos] != str2[j]) {
                        isDifferent = true;
                    }
                    // Find a position we can modify
                    if (!isFixed[pos]) {
                        changeIndex = pos;
                    }
                }
                // If already different → OK
                if (isDifferent) continue;
                // Otherwise, try to break match
                if (changeIndex != -1) {
                    result[changeIndex] = 'b'; // change to something else
                } else {
                    return ""; // no way to break match
                }
            }
        }
        return result;
    }
};