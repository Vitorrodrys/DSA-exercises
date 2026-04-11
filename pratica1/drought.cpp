#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <math.h>

using namespace std;

using namespace std;

using ConsPerHouse = int;
using PeoplePerHouse = int;
using CityMean=float;

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
    return pair(consume_per_people, (float)total_avarage_cons/(float)total_people);
}


void print_output(vector<pair<ConsPerHouse, PeoplePerHouse>> consume_list, CityMean mean_cons, int city_index){

    cout<<"Cidade# "<<city_index<<":\n";
    for(auto house_consum:consume_list){
        cout<<house_consum.second<<"-"<<house_consum.first<<" ";
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int quantity;
    int city_index=0;
    cin >> quantity;

    while (quantity !=0){
        auto input = read_consume_per_people(quantity);
        sort(input.first.begin(), input.first.end());

    }



    cout.flush();

}