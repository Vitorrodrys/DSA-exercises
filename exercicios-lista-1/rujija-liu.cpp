/**
 *  beecrowd | 1424 
 *  Easy Problem from Rujia Liu?
 */
#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<int> parse_to_int(const string& numbers){
    stringstream ss(numbers);
    string t;
    char del=' ';
    vector<int> converted;
    while (getline(ss, t, del)){
        converted.push_back(
            stoi(t)
        );
    }
    return converted;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int quantity_numbers, quantity_tests;
    string numbers_raw;

    while (cin>>quantity_numbers){
        cin>>quantity_tests;
        cin.ignore();

        getline(cin, numbers_raw);
        vector<int> numbers=parse_to_int(numbers_raw);
        assert(numbers.size() == quantity_numbers);

        unordered_map<int, vector<int>> pos_mapping;
        for(int i = 0; i<numbers.size(); i++){
            pos_mapping[numbers[i]].push_back(i);
        }

        for(int i= 0; i<quantity_tests; i++){
            int kth_ocurrence, value;
            cin>>kth_ocurrence>>value;

            if (pos_mapping.find(value) != pos_mapping.end() and kth_ocurrence <= pos_mapping[value].size())
                cout<<pos_mapping[value][kth_ocurrence-1]+1<<endl;
            else
                cout<<0<<endl;
        }

    }

    cout.flush();

}