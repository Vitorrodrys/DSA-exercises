/**
 *  beecrowd | 2506 
 *  Medical Clinic Queue
 */
#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int simulate(vector<pair<int, int>>& patients_queue){

    int critical_health_status_count=0;
    for(int current_time=7*60; current_time<24*60 and !patients_queue.empty(); current_time+=30){

        if (current_time < patients_queue[0].first) continue;


        if (current_time > patients_queue[0].second){
            critical_health_status_count++;
        }
        patients_queue.erase(patients_queue.begin());
    }
    return critical_health_status_count;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int patients_count;

    int h_arr_t, m_arr_t, time_to_critical;

    while(cin>>patients_count){
        vector<pair<int, int>> patients_queue; 
        patients_queue.reserve(patients_count);
        for(int i = 0; i<patients_count; i++){
            cin>>h_arr_t>>m_arr_t>>time_to_critical;

            patients_queue.push_back(
                pair(h_arr_t*60+m_arr_t, h_arr_t*60+m_arr_t+time_to_critical)
            );
        }
        sort(patients_queue.begin(), patients_queue.end(), [](auto v1, auto v2){
            return v1.first < v2.first;
        });
        cout<<simulate(patients_queue)<<endl;

    }


    cout.flush();

}