#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unordered_map<string, array<int, 3>*> medals_count_map;


    string competition;

    string current_country;
    array<int, 3>* country_medal_count=nullptr;
    while(getline(cin, competition)){
        for(int i = 0; i < 3; i++){
            getline(cin, current_country);
            country_medal_count = medals_count_map[current_country];
            if(country_medal_count == nullptr){
                country_medal_count = new array<int, 3>();
                medals_count_map[current_country] = country_medal_count;
            }
            (*country_medal_count)[i]+=1;

        }
    }

    vector<tuple<int, int, int, string>> elements;
    for(const auto& [key, value]: medals_count_map){
        elements.push_back(
            tuple<int, int, int, string>((*value)[0], (*value)[1], (*value)[2], key)
        );
    }

    sort(elements.begin(), elements.end(), [](auto k1, auto k2){
        if (get<0>(k1) != get<0>(k2)) return get<0>(k1) > get<0>(k2);
        if (get<1>(k1) != get<1>(k2)) return get<1>(k1) > get<1>(k2);
        if (get<2>(k1) != get<2>(k2)) return get<2>(k1) > get<2>(k2);
        if (get<3>(k1) != get<3>(k2)) return get<3>(k1) < get<3>(k2);
    });

    cout<<"Quadro de Medalhas"<<endl;
    for(auto value:elements){
        cout<<get<3>(value)<<" "<<get<0>(value)<<" "<<get<1>(value)<<" "<<get<2>(value)<<endl;
    }
    cout.flush();

}