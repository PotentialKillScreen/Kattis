using namespace std;
#include<bits/stdc++.h>

int main(){
    unsigned long  long int M,N,input, div, rem,aDiff, value;
    signed long long int diff;
    cin >> M >> N;
    unsigned long long int inputs[N];
    unsigned long long int sum = 0;
    unsigned long long int output = 0;
    for (int i = 0; i<N; i++){
        cin >> input;
        sum += input;
        inputs[i] = input;
    }
    sum = sum - M;
    div = sum/N;
    //cout << div << endl;
    sort(inputs,inputs+N);
    unsigned long long int pos = 0;
    while (true){
        input = inputs[pos];
        diff = div - input;
        if (diff >= 0){
            output += input*input;
            sum -= input;
            N--;
            div = sum/N;
            pos++;
        }
        else{
            break;
        }
    }
        
        
    rem = sum%N;
    output += div*div*(N-rem) +(div+1)*(div+1)*(rem); 
    //cout << output << endl;
    /* 
    for (int i = 0; i<N; i++){
        diff = inputs[i]- div;
      //  cout << diff << endl;
        if (diff < 0){
            aDiff = abs(diff);
            output += aDiff*aDiff + aDiff;
            //cout << output;
        }
    }
*/
    cout << output;
    return 0;
}
