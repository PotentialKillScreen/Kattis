//Author: Axel Ahlqvist
//Problem: 3.1 String matching
//Finding all matches of a pattern in a string
//Algorithm: Knuth-Morris-Pratt
//Time complexity: O(text + pattern)

#include<bits/stdc++.h>
using namespace std;

void print_vec(vector<int> vec){
//Function to print the positions
    int pLength = vec.size();
    for (int i = 0; i < pLength; i++) {
        if (vec[i] > -1){
            cout << vec[i] << ' ';
        }
    }
    cout << endl;
}

vector<int> prefixFunction(vector<char> pattern, vector<int> index,int pLength){;
//Function to produce an array where each value represent how far the substring is
//a repetition of the prefix of the string.
    index[0] = 0;
    int k = 0;
    for (int q = 1; q <pLength;q++){
        while (k > 0 && pattern[k] != pattern[q]){
            k = index[k - 1];
        }
        if (pattern[k] == pattern[q]){
            k++;
        }
        index[q] = k;
    }
    return index;
}


vector<int> KMPmatcher(vector<char> pattern, vector<char> text, vector<int> index, int pLength, int tLength) {
//Goes through the text array and uses the index of repeating patterns in order to
//not having to go through the same character multiple times.     
    int q = 0;
    int counter = 0;
    vector<int> position(tLength,-1);
    for (int i = 0; i <tLength; i++){
        while (q>0 && pattern[q] != text[i]){
            q = index[q-1];
        }
        if (pattern[q] == text[i]){
            q++;
        }
        if (q == pLength){
            if (counter > 0) {
            }
            counter++;
            position[i] = i + 1 - pLength;
            q = index[q-1];
        }
        
    } 
    return position;
} 
vector<int> find(string pattern, string text) {
//Goes through the text array and uses the index of repeating patterns in order to
//not having to go through the same character multiple times.     
    int pLength = pattern.length();
    int tLength = text.length();
    vector<int> position(tLength,-1);
    vector<char> patternVec(pLength + 1, 'a');
    vector<char> textVec(tLength + 1, 'a');
    for (int i = 0; i < pLength;i++){
        patternVec[i] = pattern[i];
    }
    for (int i = 0; i < tLength; i++){
        textVec[i] = text[i];
    }
    vector<int> index(pLength,0);     
    index = prefixFunction(patternVec,index,  pLength);
    
    position = KMPmatcher(patternVec, textVec, index, pLength, tLength);
    return position;
} 

int main() {
    string stringPattern;
    string stringText;
    while (getline(cin, stringPattern)){
        vector<int> position;
        if (stringPattern == ""){
            return 0;
        }
//input
        getline(cin, stringText);
//Algorithm
        position = find(stringPattern, stringText); 
//Output
        print_vec(position);
    }
    return 0;
}
