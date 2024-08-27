#include<bits/stdc++.h>
using namespace std;



int main(){

    int nTests;
    scanf("%d", &nTests);
    int suffixLength =0;  
    for (int i =0; i<nTests;i++){
        int nChar;
        int nSuffix;
        int cPos;
        bool impossible = false;
        scanf("%d", &nChar);
        scanf("%d", &nSuffix);
        //vector<char> outStr(nChar, ',');
        char outStr[nChar];
        for (int j = 0; j < nChar; j++){
           outStr[j] = ',';
        }
        for (int j = 0; j <nSuffix; j++){
            scanf ("%d", &cPos);
            cPos--;
            vector<char> inStr;
            string line;
            getline(cin, line);
            istringstream iss(line);
            char c;
            while (iss >> c) {
                inStr.push_back(c);
            }
            int suffixLength = inStr.size(); 
            
            //cout << "suffix Length " << suffixLength << endl;
            if (impossible) {
               // cout << "imp " << j <<endl;
                continue;
            } 
            for (int k =0; k<suffixLength; k++){
                if (inStr[k] == '*'){
                    cPos = nChar - suffixLength;
                }
                else if (outStr[cPos+ k] == ','){
                    outStr[cPos+k] = inStr[k];
                }
                else if (outStr[cPos+k] != inStr[k]){
                    impossible = true;
                    break;
                }
            }
        }
//        cout << impossible << " imposi" << endl;
        if (!impossible){ 
            //cout << suffixLength << " suffixL " << endl;
            for (int j = 0; j<nChar; j++){
               if (outStr[j] == ','){
                  impossible = true;
               }
            }
        }
        if (!impossible){ 
            //cout << suffixLength << " " << outStr[0] << endl;
            for (int j = 0; j<nChar; j++){
                printf("%c", outStr[j]);
            }
            printf("\n");
        }
        else {
            printf("IMPOSSIBLE \n");
        }
    }
    return 0;
}

