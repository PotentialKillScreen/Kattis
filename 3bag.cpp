#include<bits/stdc++.h>
using namespace std;


//Function to calculate the total number of combinations  
int calculateCombinations(int n, int k) {
    if (k > n - k) {
        k = n - k; 
    }
    long long int c = 1; 
    for (int i = 0; i < k; ++i) {
        c = c * (n - i) / (i + 1);
    }
    return c;
}

int main() {
    int T;
    cin >> T;
    for (int game = 1; game <= T; ++game) {
        int n;
        cin >> n;
        vector<int> tiles(n);
        for (int i = 0; i < n; ++i) {
            cin >> tiles[i];
        }

        int k, X;
        cin >> k >> X;

        // Dynamic programming array
        vector<vector<int>> solutions(k + 1, vector<int>(X + 1, 0));
        solutions[0][0] = 1; // Base case

    
        for (int tile : tiles) {
            for (int i = k ; i > 0; --i) {
                for (int j = X; j >= tile ; --j) {
                    solutions[i][ j] += solutions[i - 1 ][j - tile];
                }
            }
        }

        int nWinningCombinations = solutions[k][X];
        int nTotalCombinations = calculateCombinations(n, k);
        int nlosingCombinations = nTotalCombinations - nWinningCombinations;

        cout << "Game " << game << " -- " << nWinningCombinations << " : " << nlosingCombinations << endl;
    }

    return 0;
}
