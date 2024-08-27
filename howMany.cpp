#include<bits/stdc++.h>

using namespace std;

class Solver{
    private:
    public:
        long int output;
        Solver(long int,long int);
        long int nZeros(long int);
        long int mZeros(long int);
};
Solver::Solver(long int a,long int b){
    long int x = Solver::nZeros(a- 1);
    //cout << x << endl;
    long int y = Solver::nZeros(b);
    //cout << y << endl;
    Solver::output = y - x; 
}



long int Solver::mZeros(long int a){
    if (a < 0 ) {
        return 0 ;
    }
    long int count = 0;
    long int tmp;
    tmp = a;
    vector<int> digits;
    int nDigits = 1;
    digits.push_back(tmp%10);
    while (tmp /10 != 0){
        tmp = tmp/10;
        digits.push_back(tmp%10);
        nDigits++;
    }
    //cout << "nDigits " << nDigits<< endl;
    if (nDigits ==1 ){
        return 1;
    }
    for (int i = 0; i < nDigits-1; i++){
        count += digits[nDigits-1] * pow(10, nDigits -2);
        cout << "1 " << count << endl;
        for (int j= i+1; j <nDigits-1; j++){
            count += digits[j] * pow(10,j-1);
          //  cout << "2 " << count << endl;
        }
    }
    for (int i = 1; i < nDigits-1; i++){
        if (digits[i] > 0){
            count += pow(10, i);
           // cout << " 3 " << count << endl;
        }
        else{
            tmp = 0;
            for (int j = 0; j<i ; j++){
                tmp += digits[j]*pow(10, j);
            //    cout << " 4 " << count << endl;
            }
            count += tmp; 
        } 
    }
    cout << "s " << count << endl;
    tmp = 1;
    for (int i = 1; i < nDigits-1; i++){
        
        tmp += (i-1)*9*pow(10,i-2);
    }
    count += tmp; 
    cout << "t " << count << endl;
    return count;
} 
    //count += Solver::mZeros(

long int Solver::nZeros(long int a){
    if (a < 0 ){
        return 0;
    }
    long int count = 0;
    vector<int> digits;
    digits.clear();
    int nDigits = 1;
    //int temp = 1;
    long int tmp = a;
    digits.push_back(tmp%10);
    //cout << "number " << a << endl;
    while (tmp /10 != 0){
        tmp = tmp/10;
        digits.push_back(tmp%10);
        nDigits++;
    }
    if (nDigits == 1){
        return 1;
    }
    //cout << "digits " << nDigits << endl;
    for (int i = 0; i< nDigits-1; i++){
        tmp = 0;
         
        for (int j =0; j < i ; j++){
            tmp += digits[j] * pow(10,j);
        }
        if (digits[i] >0){
            count += pow(10,i);
        }
        else {
            count += tmp + 1;
        }
        //tmp = 1; 
        for (int j = i+1; j<nDigits-1; j++){
            count += (digits[j]) *pow(10,j-1);
        }
        //if (i == nDigits -2){
        count += (digits[nDigits-1] -1) * pow(10,nDigits-2);
        //}
        //else {
         //   count += (digits[nDigits-1]) *pow(10,nDigits-2);
        //}
        //tmp = pow(10,nDigits) -2;
        //count += Solver::nZeros(tmp);
    }
    tmp = 1;
    for (int i = 1; i < nDigits-1; i++){
        
        tmp += (i)*9*pow(10,i-1);
    }
    count += tmp; 
    return count;
}
int main(){
    long int a, b;
    while(true){
        cin >> a;
        cin >> b;
        //cout << "a and b " << a << " " << b << endl;
        if (a < 0 || b < 0){
            break;
        }
        Solver solver(a,b);
        cout << solver.output << endl;
    }
    cout << endl;

    return 0;
}
        

