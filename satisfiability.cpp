#include<bits/stdc++.h>
using namespace std;
bool globaloutput = false;
void printVector(vector<bool> vec){
    int n = vec.size();
    for (int i = 0; i<n; i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}
void print2dVector(vector<vector<int>> matrix){
    int n = matrix.size();
    for (int i = 0; i< n; i++){
        int m = matrix[i].size();
        for (int j = 0; j<m; j++){
             cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

tuple<bool, bool> checkSequence(vector<bool> binary, vector<vector<int>> matrix, int nClauses,vector<int> biggest, int number){
    bool output = true;
    bool impossible = false;
    int value;
    int absValue;
    //print2dVector(matrix);
    //cout << "nClauses "  << nClauses << endl;
    for (int i = 0; i<nClauses; i++){
        bool lineTrue = false;
        int nVariables = matrix[i].size();
        //cout << nVariables << endl;
        
        bool sign; 
        for (int j =0; j<nVariables; j++){
            value = matrix[i][j];
            sign = (value> 0); 
            absValue = abs(value); 
            //sign 0 if value 0 for some reason
            //
            if (binary[absValue-1] == sign){
                lineTrue = true;
                break; 
            }
        }
        if (lineTrue == false){
            output = false;
            if (biggest[i] <= number){
                impossible = true;
                break;
            }
        }
    }
    return make_tuple(output, impossible);
}
        

void recursive(vector<vector<int>> matrix, int nClauses, int nVariables, vector<bool> sequence, vector<int> biggest, int number){
/*
    if (number == nVariables){
        //printVector(sequence);
        if (checkSequence(sequence, matrix, nClauses, nVariables)){
            if (nVariables < 20){
                printVector(sequence);
            }
            globaloutput =true;
        }
        return;
    }
*/
    //bool check;
    //bool impossible;
    auto [check, impossible] = checkSequence(sequence, matrix, nClauses, biggest, number);
    if (check){ 
        //printVector(sequence);
        globaloutput = true;
        return;
    }
    if (impossible){
        return;
    }
    if (number ==nVariables){
        return;
    }
    recursive(matrix, nClauses, nVariables, sequence, biggest, number +1);
    sequence[number] = 1;
    recursive(matrix, nClauses, nVariables, sequence, biggest, number +1);
    sequence[number] = 0;
} 
    
     

int main(){
    int nCases;
    cin >> nCases;
    for (int i =0; i<nCases; i++){
        int nVariables, nClauses;
        
        cin >> nVariables;
        cin >> nClauses;
        cin.ignore();
        
        //vector<vector<int>> matrix(nClauses, vector<int>(nVariables, -1));
        vector<vector<int>> matrix(nClauses, vector<int>{});
        for (int j = 0; j<nClauses; j++){
            string temp;
            getline(cin,temp);
            char tempChar = temp[0];
            bool positive = true;
            bool Xfound= false;
            int counter = 0;
            int nChar = temp.size();
            int firstNumber = 0;
            int secondNumber = 0;
            int number;
            bool firstNumberFound = false;
            for (int k =0; k<nChar; k++){
                tempChar = temp[k];
                if (tempChar =='\0'){
                    break;
                }
                if (Xfound){
                    firstNumber = tempChar - '0';
                    if (temp[k+1] == ' ' or temp[k+1] == '\0'){
                        number = firstNumber;
                    }
                    else {
                        secondNumber = temp[k+1] - '0';
                        number = 10*firstNumber + secondNumber;
                    }
                    if (positive){
                        matrix[j].push_back(number);
                    }
                    else{
                        matrix[j].push_back(-number); 
                    }
                    positive = true;
                    Xfound = false;
                    
                }

                if (tempChar == '~'){
                    positive = false;
                }
                if (tempChar == 'X'){
                    Xfound = true;
                }
            }
        }
        vector<int> biggestV(nClauses, 0);
        for (int j = 0;j< nClauses; j++){
            int highestN = 0;
            for (int k = 0; k<matrix[j].size();k++){
                if (abs(matrix[j][k]) > highestN){
                    highestN = abs(matrix[j][k]);
                }
            } 
            biggestV[j] = highestN;
        }

        //print2dVector(matrix);
        vector<bool> sequence(nVariables,0);
        globaloutput = false;
        recursive(matrix, nClauses, nVariables, sequence, biggestV,0);
        if (globaloutput){
            cout << "satisfiable" << endl;
        }
        else{
            cout << "unsatisfiable" << endl;
        }
    }
    return 0;
}
