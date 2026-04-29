#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>

using namespace std;

int main(){

    auto comp_method = [](const array<int, 3>& v1, const array<int, 3>&v2){
        return v1[0] < v2[0];
    };
    priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp_method)> dragons(comp_method);

    int day=0;

    int time_to_train, cost;
    int total_cost=0;

    int training=0;
    int dragon_id = 0;
    while (cin>>time_to_train>>cost){
        day++;
        if (training != 0){
            dragons.push(array{cost, day,  time_to_train});
            training--;
            dragon_id++;
            continue;
        }

        if (not dragons.empty()){
            array<int, 3> next = dragons.top();
            dragons.pop();
            int day_arrived = next[1];
            int training_time = next[2];
            int cost = next[0];
            total_cost+=cost*(day-day_arrived-1);
            training = training_time;
            dragon_id++;
            continue;
        }
        training=time_to_train;
        dragon_id++;
    }

    while (not dragons.empty()){
        day++;
        if (training != 0){
            training--;
            continue;
        }
        array<int, 3> next = dragons.top();
        int day_arrived = next[1];
        int training_time = next[2];
        int cost = next[0];
        dragons.pop();
        total_cost+=cost*(day-day_arrived-1);
        training=training_time;
    }
    cout<<total_cost<<endl;
}