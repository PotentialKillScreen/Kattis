#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int MAX_DIGITS = 15;
const int MAX_SUM = 135;

long long dp[MAX_DIGITS][MAX_SUM][2];
long long dpMin[MAX_DIGITS][MAX_SUM][2][2];

void fillDigits(long long num, int digits[]) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        digits[i] = num % 10;
        num /= 10;
    }
    reverse(digits, digits + MAX_DIGITS);
}

long long countNumbers(int pos, int sum, bool tight, int digits[]) {
    if (sum < 0) return 0;
    if (pos == MAX_DIGITS) return sum == 0;
    if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];
    int limit = tight ? digits[pos] : 9;
    long long result = 0;
    for (int i = 0; i <= limit; ++i) {
        result += countNumbers(pos + 1, sum - i, tight && (i == limit), digits);
    }
    return dp[pos][sum][tight] = result;
}
void printDigits(int digits[]) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        cout << digits[i] << " ";
    }
    cout << endl;
}
long long countInRange(long long num, int S) {
    int digits[MAX_DIGITS];
    fillDigits(num, digits);
    //cout << "Digits: ";
    //printDigits(digits);
    memset(dp, -1, sizeof(dp));
    return countNumbers(0, S, true, digits);
}

void printDP(long long dp[MAX_DIGITS][MAX_SUM][2]) {
    for (int i = 0; i < MAX_DIGITS; i++) {
        for (int j = 0; j < MAX_SUM; j++) {
            for (int k = 0; k < 2; k++) {
                if (dp[i][j][k] != -1) {
                    cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << endl;
                }
            }
        }
    }
}

long long findSmallestNumber(long long A, int pos, int sum, int digits[], long long current) {
    if (sum < 0) return -1;
    if (pos == MAX_DIGITS) return sum == 0 && current >= A ? current : -1;
    //int limit = tight ? digits[pos] : 9;
    for (int i = 0; i <= 9; ++i) {
        long long next = findSmallestNumber(A, pos + 1, sum - i, digits, current * 10 + i);
        if (next != -1) return next;
    }
    return -1;
}

int numbDigits(long long num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

int digitSum(long long num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

long long findSmallestInRange(long long A, int minNumbDigits, int sum) {
    int A_numbDigits = numbDigits(A);
    int A_digitSum = digitSum(A);
    long long int current = 0;
    int currentDigit = 1;
    if (A_numbDigits < minNumbDigits) {
        while (sum > 0){
            if (sum > 9){
                sum -= 9;
                current += 9 * pow(10, currentDigit-1);
            }
            else {
                current += sum * pow(10, currentDigit-1);
                sum = 0;
            }
            currentDigit++;
            
        }
        return current;
    }
    int A_digits[MAX_DIGITS];
    fillDigits(A, A_digits);
    current = 0;
    currentDigit = 1;
    int A_currentIndex = 14;
    int missingSum = sum - A_digitSum;
    for (int A_currentIndex = 14; A_currentIndex >= 0; A_currentIndex--) {
        if (missingSum == 0){
            current += A_digits[A_currentIndex]  * pow(10, currentDigit-1);
        }
        else if (missingSum > (9-A_digits[A_currentIndex])){
            current += 9* pow(10, currentDigit-1);
            missingSum -= (9 - A_digits[A_currentIndex]);
        }
        else{
            current += (missingSum + A_digits[A_currentIndex])* pow(10, currentDigit-1);
            missingSum = 0;
        }
        currentDigit++;
    }
    return current;
}
int findMinNumbDigitsDP(int sum, long long dp[MAX_DIGITS][MAX_SUM][2]) {
    for (int i = MAX_DIGITS -1; i >= 0; i--) {
        for (int k = 0; k<2;k++) {
            if (dp[i][sum][k] > 0) {
                return MAX_DIGITS - i;
            }
        }        
    }
    return -1;
}

int main() {
    long long A, B;
    int S;
    cin >> A >> B >> S;
    // Start clock to see how long time execution takes
    clock_t start = clock();
    long long  BS = countInRange(B, S);
    //SprintDP(dp);
    int minNumbDigits = findMinNumbDigitsDP(S,dp);
    long long AS = countInRange(A - 1, S);
    //cout << BS << endl;
    //cout << AS << endl;
    cout << BS - AS << endl;


    // Print dp array
    //printDP(dp);

    cout << findSmallestInRange(A,minNumbDigits, S) << endl;
    // End clock to see how long time execution takes
    clock_t end = clock();
    //cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
    return 0;
}