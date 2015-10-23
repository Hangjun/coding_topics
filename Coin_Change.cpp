Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins, how many ways can we make the change? The order of coins doesn’t matter.

For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4. For N = 10 and S = {2, 5, 3, 6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.


/* Dynamic Programming: O(mn) Time, O(mn) Space */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int coinChange(vector<int> changes, int n) {
    // corner cases
    if (changes.empty() && n > 0) return 0;
    if (n < 0) return 0;
    int m = changes.size();
    // dp[i][j] = #ways to fill j cents with change[0,..., i-1] different changes
    // return dp[m][n]
    vector<vector<int>> dp(m, vector<int>(n+1));
    // initialize dp
    for (int i = 0; i < m; i++) {
        dp[i][0] = 1;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            // transfer function:
            // dp[i][j] = dp[i-1][j] + dp[i][j-changes[i]]
            int x = (j >= changes[i]) ? dp[i][j-changes[i]] : 0;
            int y = (i > 0) ? dp[i-1][j] : 0;
            dp[i][j] = x + y;
        }
    }
    return dp[m-1][n];
}

int main() {
    vector<int> changes = {2, 5, 3, 6};
    cout << coinChange(changes, 10) << endl;
	return 0;
}
