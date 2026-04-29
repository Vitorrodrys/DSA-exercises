/*
 beecrowd | 2720 
 Large Presents
*/

#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void check(){
    int quantity_santa_claus_gifties, k_allowed;
    cin>>quantity_santa_claus_gifties>>k_allowed;

    vector<pair<int, int>> gifties;
    int g_id, g_height, g_width, g_lenght;
    for (int j = 0; j<quantity_santa_claus_gifties; j++){
        cin>>g_id>>g_height>>g_width>>g_lenght;
        gifties.push_back(
            pair(g_height*g_width*g_lenght, g_id)
        );
    }
    sort(gifties.begin(), gifties.end(), [](auto v1, auto v2){
        if (v1.first != v2.first) return v1.first > v2.first;
        return v1.second < v2.second;
    });

    sort(gifties.begin(), gifties.begin()+k_allowed, [](auto v1, auto v2){
        return v1.second < v2.second;
    });
    reverse(gifties.begin(), gifties.end());
    for(int i = 0; i<k_allowed-1; i++){
        cout<<gifties[i].second<<" ";
    }
    cout<<gifties[k_allowed-1].second<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int quantity_test_cases;
    cin>>quantity_test_cases;

    for(int i = 0; i<quantity_test_cases; i++){
        check();
    }


    cout.flush();

}