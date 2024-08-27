#include<bits/stdc++.h>
using namespace std;

void printVector(vector<int> vect){
    for (int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
    }
}

int main(){

    int nStrings;
    

    cin >> nStrings;
    cin.ignore();
    //scanf("%d", &nStrings);
    for (int i = 0; i<nStrings; i++){
        int nCharacters;
        string str;
        getline(cin,str);
        nCharacters = str.length();
        //cout << str << " " << nCharacters <<  endl;
        map<char,int> occurrences;
        map<char,int> cOccurrences;
        map<char,vector<int>> positions;
        vector<int> dist(nCharacters,0);
        bool foundCenter = false;
        bool done = false;
        char center;
        bool centerPlaced = false;
        bool oddNChar = true;
        int temp;
        int nSwitch = 0;
        if ( nCharacters % 2 == 0){
            oddNChar = false;
        }
        //cout << "oddnchar " << oddNChar << endl;
        for (int j =0; j<nCharacters;j++){
            char c = str[j]; 
            if (occurrences.find(c) == occurrences.end()){
                occurrences[c] =1;
            }
            else{
                occurrences[c] +=1;
            }
        }    
        
        for (map<char,int>::iterator it = occurrences.begin(); it != occurrences.end(); it++){
            
            char c = it->first; 
            //cout << occurrences[c] << endl;     
            cOccurrences[c] = 0;
            if (occurrences[c] % 2 == 0){
                occurrences[c] /= 2;
            }
            else if (!foundCenter && oddNChar){
                foundCenter = 1;
                center = c;
                occurrences[c] /= 2;
            }
            else{
                done = true;
                break;
            } 
        }

        if (done){
            cout << "Impossible" << endl;
            continue;
        }
        int original = 0;
        if (oddNChar){
            for (int j =0; j<nCharacters;j++){
                char c = str[j]; 
                cOccurrences[c]++;
                if (cOccurrences[c] <= occurrences[c]){
                    positions[c].push_back(original);
                    dist[j] = original;
                    original++;
                }
                else if (c == center && !centerPlaced){
                        dist[j] = nCharacters/2;
                        centerPlaced = true;
                }

                else{
                    dist[j] = nCharacters-positions[c].back() - 1; 
                    positions[c].pop_back(); 
                }
            }
        }
        else{ 
            for (int j =0; j<nCharacters;j++){
                char c = str[j]; 
                cOccurrences[c]++;
                if (cOccurrences[c] <= occurrences[c]){
                    positions[c].push_back(original);
                    dist[j] = original;
                    original++;
                }
                else{
                    dist[j] = nCharacters-positions[c].back() - 1;
                    positions[c].pop_back(); 
                }
            }
        }
        //cout << "dist" << endl;
        //printVector(dist);
        //cout << "after dist " << endl;
        bool sorted = false;
        int it = 0;
        bool tempb1 = false;
        int tempC = 0;  
        
        while (true){
            /*
            sorted = true;
            for (int j =0; j<nCharacters-1 ; j++){
               if (dist[j] > dist[j+1]){  
                    temp = dist[j + 1];
                    dist[j + 1] = dist[j];
                    dist[j] = temp;
                    nSwitch++;
                    sorted = false;
               }
            }
            if (sorted){
                break;
            }
*/
            if (it == nCharacters -1){
                break;
            }
            if (dist[it] <= dist[it+1]){ 
                it++; 
            }
            else {
                temp = dist[it + 1];
                dist[it + 1] = dist[it];
                dist[it] = temp;
                nSwitch++;
                if (it > 0){
                    it--;
                }
            }
            //if (it == nCharacters -1){
             //   break;
            //}
            //if (dist[it] < dist[it+1]){ 
            //}
            //else {
             //   it--;
            //}
            //it++; 
        }
        cout << nSwitch << endl; 
    }
    cout << endl;
    return 0;
}
         

        



    
