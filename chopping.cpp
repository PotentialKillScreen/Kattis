#include<bits/stdc++.h>
using namespace std;
template<typename K, typename V>

void print_map(std::unordered_map<K,V> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

void print_array(int arr[], int nElements){
    //int nElements = sizeof(arr)/sizeof(*arr);
    //cout << nElements;

    for (int i = 0; i < nElements; i++){
        //cout << arr[i] << endl;
        printf("%d\n", arr[i]);
    }
}

int main()
{
    int nVertexes, temp, reducedElement;
    
    cin >> nVertexes;
    //nVertexes++;
    //cout << nVertexes;
    int vArray[nVertexes];
    int printArray[nVertexes];
    unordered_map<int, int> frequencies;
    for (int i = 0; i < nVertexes;i++){
        frequencies[i+1] = 0;
        cin >> temp;
        vArray[i] = temp;
    }
    if(vArray[nVertexes-1] != nVertexes + 1){
        cout << "Error";
        return 0;
    }
    frequencies[nVertexes] = 0; 
    for (int i = 0; i < nVertexes; i++) {
        frequencies[vArray[i]]++;
    }
    //print_map(frequencies);
   // time to implement algorithm!
   //
    int element = 1; 
    int foundElement = 0;
    while (foundElement < nVertexes){
        
        if (frequencies[element] == 0) {
            //foundElement = element + 1;
            reducedElement = vArray[foundElement];
            printArray[foundElement] = element;
            foundElement++;
            frequencies[reducedElement]--; 
            while (frequencies[reducedElement]==0 && reducedElement < element){
                printArray[foundElement] = reducedElement;
                reducedElement =vArray[foundElement]; 
                frequencies[reducedElement]--;
                foundElement++;  
            }
        }        
        element++;
    }
/*
        if (element > nVertexes + 1){
            cout << "Error" << endl;
            return 0; 
        }
    }
*/
   /* 
    
       

    for (int i = 0; i < nVertexes; i++){
        for (int j = 1; j < nVertexes + 1; j++){
            if (frequencies[j] == 0){
                frequencies[j] = -1;
                //cout << i << " " << j << endl;
                //cout << "freq " << frequencies[vArray[i]];
                frequencies[vArray[i]]--;
                printArray[i] = j;
                //cout << " new " << frequencies[vArray[i]] << endl;
                break; 
            
                //if (
            }
            if (j == nVertexes){
                cout << "Error" << endl;
                return 0; 
            }
        }
    }
*/
    print_array(printArray, nVertexes);
    //for (int i = 0; i < nVertexes; i++){
        

    //}
    
    return 0;
}
