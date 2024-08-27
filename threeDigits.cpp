#include <bits/stdc++.h>
using namespace std;

int lastThreeDigitsBeforeTrailingZeros(int n) {
    long long int result = 1;
    long long int count_2 = 0, count_5 = 0;

    for (long long int i = 1; i <= n; i++) {
        long long int num = i;
        
        while (num % 2 == 0) {
            num /= 2;
            count_2++;
        }
        while (num % 5 == 0) {
            num /= 5;
            count_5++;
        }
        
        result = (result * num) % 1000;
    }
    
    for (long long int i = 0; i < count_2 - count_5; i++) {
        result = (result * 2) % 1000;
    }
    
    return result;
}

int main() {
    long long int n;
    cin >> n;

    long long int result = lastThreeDigitsBeforeTrailingZeros(n);
    if (n < 8){
        cout << result << endl;
    } else if (result < 10) {
        cout << "00" << result << endl;
    } else if (result < 100) {
        cout << "0" << result << endl;
    } else {
        cout << result << endl;
    }
    return 0;
}