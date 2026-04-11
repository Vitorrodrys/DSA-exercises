#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

using namespace std;

int binary_search(int merbles[], int marbles_size, int target){
    int begin=0;
    int end=marbles_size-1;
    int half=begin+(end-begin)/2;

    while(begin<end and merbles[half] != target){
        if(merbles[half] < target){
            begin=half+1;
        }else{
            end=half-1;
        }
        half=begin+(end-begin)/2;
    }
    return (target==merbles[half])?half:-1;
}

int exclude_equals(int marbles[], int index_target){
    int target=marbles[index_target];
    int backward_index=1;

    do{
        index_target=index_target-(backward_index/2);
        backward_index=1;

        while (index_target-backward_index >= 0 and marbles[index_target - backward_index] == target){
            backward_index*=2;
        }
    }while(backward_index > 1);
    return index_target;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int merbles_quant, queries_quant, current_query;
    int merble_index=0;
    int case_index=1;

    cin >> merbles_quant >> queries_quant;

    while (merbles_quant != 0 and queries_quant !=0){
        int merbles_vector[merbles_quant]={0};

        for(int i = 0; i< merbles_quant; i++){
            cin >> merbles_vector[i];
        }
        sort(merbles_vector, merbles_vector+merbles_quant);

        cout<<"CASE# "<<case_index<<":\n";
        for(int i = 0; i < queries_quant; i++){
            cin>>current_query;

            merble_index=binary_search(merbles_vector, merbles_quant, current_query);
            if (merble_index == -1){
                cout<<current_query<<" not found"<<endl;
                continue;
            }
            merble_index=exclude_equals(merbles_vector, merble_index);
            cout<<current_query<<" found at "<<merble_index+1<<endl;
        }

        cin >> merbles_quant >> queries_quant;
        case_index++;
    }
    cout.flush();


}