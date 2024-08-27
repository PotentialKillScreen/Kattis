//Author: Axel Ahlqvist
//Problem: Interval Cover
//Finding a minimum number of intervals that covers an objective interval
//Algorithm: Greedy algorithm
//Time complexity: O(NlogN)
#include<bits/stdc++.h>
using namespace std;

int printVectorD(vector<pair<double,double>> path){
    for (int i = 0; i < path.size();i++){
        cout << path[i].first << " " << path[i].second <<endl;
    }
    return 0;
}

//Function to print a vector, for debugging 
int printVector(vector<double> path){
    for (vector<double>::const_iterator i = path.begin(); i != path.end(); ++i)
        cout << *i << ' ';
    return 0;
}

int printVectorInt(vector<int> path){
    for (vector<int>::const_iterator i = path.begin(); i != path.end(); ++i)
        cout << *i << ' ';
    return 0;
}


//A function which takes a vector of doubles, sorts it in ascending order and 
//return a vector with the original indexes but in sorted order. This allows translation between
//original and sorted position. 
vector<int> sort_indexes(vector<double> &v) {
  vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);
  stable_sort(idx.begin(), idx.end(),
       [&v](int i1, int i2) {return v[i1] < v[i2];});
  return idx;
}


//Main function that takes an objective interval, as a pair, and a vector of intervall as input.
//Returns a vector with the indexes of intervalls that covers the objective intervalls. 
//If it is not possible to cover the objective intervall, then 
//an empty vector is returned. 
vector<int> cover(pair<double,double> interval, vector<pair<double,double>> intervals){
    vector<int> sortedIdx;
    vector<double> startValues;
    //add a final interval in order to not get out of bounds
    intervals.push_back({DBL_MAX,DBL_MAX});
    for (int i = 0; i<intervals.size();i++){
        startValues.push_back(intervals[i].first);
    }
    //Sort based on the interval starting values
    sortedIdx = sort_indexes(startValues);
    vector<int> vect;
    double start = interval.first;
    double end = interval.first -1; 
    int tmpIdx;
    //Go through all the intervals. When finding an interval that starts after the end point, add the interval
    //that went the furthest, set that intervalls end point as the new end point and continue.
    for (int i = 0; i< intervals.size();){
        if (intervals[sortedIdx[i]].first <= start){
            if (intervals[sortedIdx[i]].second > end){
                end = intervals[sortedIdx[i]].second;
                tmpIdx = sortedIdx[i];
            }
            i++;
        }
        else{    
            vect.push_back(tmpIdx);
            start = end;
            if ((intervals[sortedIdx[i]].first > end) || (end >= interval.second)){
              break; 
            }
        }
        
    }
    if (end < interval.second){
        vector<int> empty{};
        return empty;
    }
    else {
        return vect;
    }
}


//Function to print the vector of indices in the desired format. If the vector is empty, thenn 
//'impossible' is printed.
void print_output(vector<int> indices){
    int nIndices = indices.size();

    if (nIndices > 0){
        cout << indices.size() << endl;
        for (int i = 0; i<indices.size(); i++){
            cout << indices[i] << " ";
        }   
        cout << endl;
    }   
    else {
        cout << "impossible" << endl;
    }
}   


int main(){
    string stringInterval, stringNumber;
//Process input as long as new line as inputed.
//First input the two intervalls defining the objective intervall.
    while(getline(cin, stringInterval)){ 
        if (stringInterval == "") {
            break;
        }
        double start, end; 
        stringstream intervalstream(stringInterval);
        int nIntervals;
        intervalstream >> start;
        intervalstream >> end;
        pair<double,double>interval(start,end);
        //Input the number of intervall candidates.
        getline(cin, stringNumber);
        nIntervals = stof(stringNumber);
        pair<double,double> example(0,0); 
        vector<pair<double,double>> intervals(nIntervals, example); 
        vector<int> indices;
        
        for (int i = 0; i < nIntervals; i++){
            //for each candidate interval input the start and the end of that interval.
            getline(cin, stringInterval);
            stringstream intervalstream(stringInterval);
            intervalstream >> intervals[i].first;
            intervalstream >> intervals[i].second;
        }
        //Calculates a partition of the minimum number of indices needed to cover the
        //objective intervall. If the objective intervall can not be covered then the
        //vector is empty and the output have been printed. 
        indices = cover(interval,intervals); 
       //Prints the output. 
        print_output(indices);
    }
    return 0;
}
