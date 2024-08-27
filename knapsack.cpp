//Author: Axel Ahlqvist
//Problem: Knapsack 
//Finding the items that maximizes value given limited packing capacity
//Algorithm: Dynamic programming
//Time complexity: O(number_of_items * capacity)

#include<bits/stdc++.h>
using namespace std;

//Function to print a vector for debugging.
int printVector(vector<int> vec){
    for (int i = 0; i <vec.size();i++){
        cout << vec[i] << " ";
    }
    cout << endl;
    return 0;
}

//Function to print the contents of a 2d vector for debugging.
int print2DTable(vector<vector<int>> kTable){
    int rows = kTable.size();;
    int cols = kTable[0].size();
    for (int i =0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            cout << kTable[i][j] << ", ";
        }
        cout << endl;
    }
    return 0;
}


//Function that takes a capacity, a vector of values and a vector of weights 
//and return a vector of the indexes of items that maximizes the total value
//while not exceeding the capacity.
vector<int> knapsack(int capacity, vector<int> values, vector<int> weights){
    vector<int> output{};
    int nItems = values.size();
    //Creates a table which in each cell store the highest value that can be 
    //achieved given the first items up to the row number, given the capacity
    //of the column number. The first row and column contains 0 and represents
    //no item.
    vector<vector<int>> kTable(nItems+1,vector<int>(capacity+1));
    for (int i = 0; i <= nItems; i++){
        for (int j = 0; j <= capacity; j++){
            if (i == 0 || j == 0){
                kTable[i][j] = 0;
            }
            else if (weights[i-1] <= j){
                kTable[i][j] = max(values[i-1] + kTable[i-1][j-weights[i-1]], kTable[i-1][j]);
            }
            else
                kTable[i][j] = kTable[i-1][j];
        }
    }
    //Backtracks through the table and extract the items that where used to generate 
    //the highest total value
    int cumValue = kTable[nItems][capacity];
    int cumCap = capacity;
    for (int i = nItems; i > 0 && cumValue > 0; i--){
        if (cumValue == kTable[i-1][cumCap]){
            continue;
        }
        else {
           output.push_back(i-1);
           cumValue = cumValue - values[i-1];
           cumCap = cumCap - weights[i-1]; 
        }
    }
    return output;
}

//Function to print the results in the desired format.
int printOutput(vector<int> indexes){
    cout << indexes.size();
    cout << endl;
    for (int i = 0; i < indexes.size(); i++){
        if (i > 0){
            cout << " ";
        }
        cout << indexes[i];
    }
    cout << endl;
    return 0;
}


int main(){
    string input; 
//Process input as long as a new line is inputed.
//First input the capacity and then the number of objects.
    while(getline(cin,input)){
        if (input == ""){
            break;
        }
        int capacity,nItems;
        stringstream inputStream(input);
        inputStream >> capacity;
        inputStream >> nItems;
        vector<int> values (nItems,0);
        vector<int> weights (nItems,0);
        
    //For each item input the value and then the weight. 
        for (int i = 0; i<nItems; i++){
            string inputItem;
            getline(cin,inputItem);
            stringstream itemStream(inputItem);
            int tmpValue,tmpWeight;
            itemStream >> tmpValue;
            itemStream >> tmpWeight;
            values[i] = tmpValue;
            weights[i] = tmpWeight;
        }
        vector<int> indexes;
        //Calculates the indexes of the items that maximizes the total value 
        //while not exceeding the capacity
        indexes = knapsack(capacity, values, weights);
        //prints the output as the number of items, followed by a line with 
        //the indexes of the items used. 
        printOutput(indexes);
    }
        return 0;

}
