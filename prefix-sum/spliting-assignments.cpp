/**
 *  beecrowd | 2715 
 *  splitting assignments
 */

#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>



using namespace std;

vector<long long int> make_prefix_sum(vector<long long int> input){
    vector<long long int> prefix_sum(input.size()+1, 0);

    for(int i = 1; i<input.size()+1; i++){
        prefix_sum[i] = input[i-1] + prefix_sum[i-1];
    }
    return prefix_sum;
}

vector<long long int> make_suffix_sum(vector<long long int> input){
    vector<long long int> suffix_sum(input.size()+1, 0);

    for(int i = input.size()-1; i >= 0; i--){
        suffix_sum[i] = suffix_sum[i+1] + input[i];
    }
    return suffix_sum;
}

int main(){

    int quantity_assignments;

    int current;
    while (cin>>quantity_assignments){

        vector<long long int> assignments;

        assignments.reserve(quantity_assignments);
        for(int i = 0; i<quantity_assignments; i++) {
            cin>>current;
            assignments.push_back(current);
        }

        vector<long long int> prefix_sum = make_prefix_sum(assignments);
        vector<long long int> suffix_sum = make_suffix_sum(assignments);
    
        long long int smallest;
        memset(&smallest, 1, sizeof(smallest)-1);
        long long int assignment_diff;
        for(int i = 1; i<=assignments.size(); i++){
            assignment_diff = abs(prefix_sum[i] - suffix_sum[i]);
            smallest = min(smallest, assignment_diff);
        }
        cout<<smallest<<endl;


    }
}
