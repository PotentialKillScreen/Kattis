//Author: Axel Ahlqvist
//Problem: suffix sort
//Data structure that sorts the the suffixes of a string in lexigraphical order
//Algorithm: Suffix array
//Time complexity: O(s log s) for contruction and O(1) for access
//Memory complexity(s logs)
#include<bits/stdc++.h>
using namespace std;



struct suffix {
    int index;
    int rank[2];
};


typedef struct suffix suffix;
class Suffix_Array{

    public:
        vector<int> vec;
        Suffix_Array(string text);
        int getSuffix(int index);
};
int comp(suffix a, suffix b){
//Function to compare rank of suffixes, return 1 if b is greater, otherwise 0 
//This function is necessary for the sort function.
    if (a.rank[0] > b.rank[0]){
        return 0;
    }
    if (b.rank[0] > a.rank[0]){
        return 1; 
    }
    if (a.rank[1] > b.rank[1]){
        return 0;
    }
    if (b.rank[1] > a.rank[1]){    
        return 1;
    }
    return 0;
}
Suffix_Array::Suffix_Array(string txt){
//Takes a string of text and builts a structure with the suffixes lexiographically sorted.
    int n = txt.length(); 
    vector<int> tmpVec (n, 0);
    vec = tmpVec;
    int inf = numeric_limits<int>::max();
    suffix suffixes[n];
//Rank is set based on the first letter and the next letter. 
    for (int i = 0; i < n; i++){

        suffixes[i].rank[0] = txt[i] - 'a';

        if (i < n-1){
            suffixes[i].rank[1] = txt[i+1] -'a';
        }
        else {
            suffixes[i].rank[1] = -inf;
        }

        suffixes[i].index = i;
    }
 
    sort(suffixes, suffixes+n, comp);
 
    int indexes[n];  
//Sorting based on i characters is being done until completely sorted.
    for (int i = 4; i < 2*n; i = i*2) {
        int rank = 0;
        int prevRank = suffixes[0].rank[0];
//indexes vector is used to map original index to sorted indexes
        indexes[suffixes[0].index] = 0;
        suffixes[0].rank[0] = rank;
         
        for (int j = 1; j < n; j++) {
            if (suffixes[j].rank[0] == prevRank && suffixes[j].rank[1] == 
                    suffixes[j-1].rank[1]){
                prevRank = suffixes[j].rank[0];
                suffixes[j].rank[0] = rank;
            }
            else {
                prevRank = suffixes[j].rank[0];
                rank++;
                suffixes[j].rank[0] = rank;
            }
            indexes[suffixes[j].index] = j;
        }

        for (int j = 0; j < n; j++) {
            int nextIndex = suffixes[j].index + i/2;

            if (n > nextIndex) {
                suffixes[j].rank[1] = suffixes[indexes[nextIndex]].rank[0];
            }
            else{
                suffixes[j].rank[1] = -1;
            }

        }
        sort(suffixes, suffixes+n, comp);
    }
 
    vector<int> suffixVec(n,0);
    for (int i = 0; i < n; i++){
        vec[i] = suffixes[i].index; 
    }
    Suffix_Array::vec = vec; 
}
int Suffix_Array::getSuffix(int index){
    return Suffix_Array::vec[index]; 
}
void print_output(Suffix_Array suffixArray,vector<int> positions){ 
//Prints the queried positions of the sorted suffixes.
    for (int j = 0; j <positions.size(); j++){
        int i = positions[j]; 
        int position;
        position = suffixArray.getSuffix(i);
        cout << position;  
        if (j < positions.size()-1){
           cout << " "; 
        }
    }
    cout << endl;
}
int main()
{
    string txt;
    while (true){ 
//input text
        getline(cin,txt); 
        if (txt == ""){
            break;
        }
        int nPositions;
//input number of queries
        cin >> nPositions;
        cin.ignore();
        vector<int> positions;
        for (int i=0; i<nPositions; i++){
            int tmp;
//input queries
            cin >> tmp;
            cin.ignore();
            positions.push_back(tmp);
        }
        int n = txt.length();
//Implements a suffix array which contains lexiographically sorted suffixes
        Suffix_Array suffixArray(txt);
//output function
        print_output(suffixArray, positions);
    }
    cout << endl;
    return 0;
}
