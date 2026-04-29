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


int check_nonoptimal(int i, vector<long long int>& preffix_sum, vector<long long int>& suffix_sum){

    int current_diff = abs(preffix_sum[i] - suffix_sum[i]);
    int back_diff = abs(preffix_sum[i-1] - suffix_sum[i-1]);
    int front_diff = (i+1 < preffix_sum.size())?(abs(preffix_sum[i+1] - suffix_sum[i+1])):99999;

    if (back_diff<current_diff) return 1;
    if (front_diff<current_diff) return 2;
    return 0;
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
    

        int left = 0;
        int right = assignments.size();
        int middle = right/2;
        int has_diff = check_nonoptimal(middle, prefix_sum, suffix_sum);
        while (has_diff){
            if (has_diff==1){
                right=left + (right-left)/2;
            } else {
                left=middle;
            }
            middle = left + (right-left)/2;
            has_diff=check_nonoptimal(middle, prefix_sum, suffix_sum);

        } 
        cout<< abs(prefix_sum[middle] - suffix_sum[middle])<<"\n";


    }
}