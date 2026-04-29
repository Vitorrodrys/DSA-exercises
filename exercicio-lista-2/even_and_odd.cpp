/**
 *  beecrowd | 1259 
 *  Even and Odd
 */
#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>


using namespace std;


int main(){

    int quantity;
    vector<int> numbers;

    cin>>quantity;
    numbers.reserve(quantity);

    int current;
    for(int i = 0; i<quantity; i++){

        cin>>current;
        numbers.push_back(current);
    }

    auto is_even = [](auto v){
        return v % 2 == 0;
    };
    sort(numbers.begin(), numbers.end(), [&is_even](auto v1, auto v2){
        if (is_even(v1) and  is_even(v2)) return v1 < v2;
        if (!is_even(v1) and  !is_even(v2)) return v1 >= v2;
        if (is_even(v1) and  !is_even(v2)) return true;
        if (!is_even(v1) and  is_even(v2)) return false;
    });

    for(auto v:numbers){
        cout<<v<<endl;
    }
}