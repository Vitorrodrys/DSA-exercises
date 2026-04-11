#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define POSSIBLE_NUMBERS 2000

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int quantity_inputs;

    cin >> quantity_inputs;

    int count_mapping[POSSIBLE_NUMBERS+1]={0};
    int current;

    for (int i = 0; i< quantity_inputs; i++){
        cin>>current;
        count_mapping[current]++;
    }

    for(int i = 0; i<POSSIBLE_NUMBERS+1;i++){
        if (count_mapping[i] != 0){
            cout<<i<<" aparece "<<count_mapping[i]<<" vez(es)"<<endl;
        }
    }

    cout.flush();

}