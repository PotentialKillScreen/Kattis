#include<bits/stdc++.h>
using namespace std;

bool isPattern(string word){
    return ((word.at(0) == '<') && (word.back() == '>')); 
}

bool isSame(string word1, string word2){
    return ((word1 == word2) || (isPattern(word1) && isPattern(word2)));
}
int main(){
    int nSentences, nWords1, nWords2;
    string line1, line2,temp, word1, word2;
    getline(cin,temp);
    nSentences = stoi(temp);
    for (int i = 0; i < nSentences; i++){
        getline(cin,line1); // grabs entire line after user presses enter;
        getline(cin,line2);
        istringstream iss1(line1); // put input string in stream
        istringstream iss2(line2);
        nWords1 = 0;
        vector<string> words1(istream_iterator<string>(iss1),istream_iterator<string>{}); // populate vector with "words"
        vector<string> words2(istream_iterator<string>(iss2),istream_iterator<string>{}); // populate vector with "words"
        istringstream issTemp1(line1);
        while (issTemp1 >> temp){
            nWords1++;
        }
        nWords2 = 0;
        
        istringstream issTemp2(line2);
        while (issTemp2 >> temp){
            nWords2++;
        }
        if (nWords1 != nWords2){
            cout << "-" << endl;
            continue;
        }

        //cout << nWords << endl;
/*
        for(vector<string>::iterator j = words1.begin(); j != words1.end(); ++j)
        {
            cout << *j << endl; // display each word on its own line
        }
        cout << endl;
        for(vector<string>::iterator j = words2.begin(); j != words2.end(); ++j)
        {
            cout << *j << endl; // display each word on its own line
        }
*/ 
        //cout << "does this work? " << words1[1] << " " << words2[1] << endl; 
        for (int j = 0; j<nWords1; j++){
            word1 = words1[j];
            word2 = words2[j];
            if (isPattern(word1) && !isPattern(word2)){
                replace(words1.begin(), words1.end(), word1, word2);
                //replace(words2.begin(), words2.end(), word1, word2);
                //cout << "replace " << endl;
                j = -1;
            }

            if (isPattern(word2) && !isPattern(word1)){
                //replace(words1.begin(), words1.end(), word2, word1);
                replace(words2.begin(), words2.end(), word2, word1);
                j = -1;
                //cout << "replace " << endl;
            } 
        }
        bool same = true;
        for (int j = 0; j<nWords1; j++){
            same = same & isSame(words1[j],words2[j]);
            //cout << words1[j] << " ";
        }

        if (same){
            for (int j = 0; j<nWords1; j++){
                word1 = words1[j];
                if (isPattern(word1)){
                    cout << "a";
                }
                else
                {
                    cout << word1 ;
                }
                if (j != nWords1 - 1){
                    cout << " ";
                }
            }
        }
        else {
        cout << "-";
        }
        cout << endl;
    }
    cout << endl;
	return 0;
}




