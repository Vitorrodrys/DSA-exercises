#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <math.h>

using namespace std;


using ConsPerHouse = int;
using PeoplePerHouse = int;
using CityMean=double;

pair<vector<pair<ConsPerHouse, PeoplePerHouse>>, CityMean> read_consume_per_people(int quantity){

    vector<pair<int, int>> consume_per_people;
    consume_per_people.reserve(quantity);
    int total_avarage_cons=0;
    int total_people=0;

    int house_people=0;
    int consume_house=0;
    for(int i = 0; i<quantity; i++){
        cin >> house_people;
        cin >> consume_house;

        consume_per_people.push_back(pair(consume_house/house_people, house_people));
        total_avarage_cons+=consume_house;
        total_people+=house_people;
    }
    return pair(consume_per_people, ((double)total_avarage_cons)/((double)total_people));
}


vector<pair<ConsPerHouse, PeoplePerHouse>> pos_processing(vector<pair<ConsPerHouse, PeoplePerHouse>> consumes){
    auto last=consumes[0];

    vector<pair<ConsPerHouse, PeoplePerHouse>> result;
    result.reserve(consumes.size());
    for (auto it = consumes.begin() + 1; it != consumes.end() - 1; ++it){   
        if (last.first == (*it).first){
            last.second+=(*it).second;
        }else{
            result.push_back(last);
            last=*it;
        }
    }

    if (consumes.back().first == last.first){
        last.second+=consumes.back().second;
        result.push_back(last);
    }else{
        result.push_back(last);
        result.push_back(consumes.back());
    }

    return result;
}


void print_output(vector<pair<ConsPerHouse, PeoplePerHouse>> consume_list, CityMean mean_cons, int city_index){

    cout<<"Cidade# "<<city_index<<":\n";
    for(auto house_consum:consume_list){
        cout<<house_consum.second<<"-"<<house_consum.first<<" ";
    }
    cout<<"\nConsumo medio: "<<std::fixed<<std::setprecision(2)<<floor(mean_cons*100)/100<<" m3."<<endl<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int quantity;
    int city_index=1;
    cin >> quantity;

    while (quantity !=0){
        auto input = read_consume_per_people(quantity);
        sort(input.first.begin(), input.first.end());
        auto result = pos_processing(input.first);
        print_output(result, input.second, city_index);
        city_index++;
        cin>>quantity;

    }



    cout.flush();
    return 0;
}