#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


vector<string> extract_connected_components(vector<vector<int>>& g){

    list<int> q(g.size());
    iota(q.begin(), q.end(), 0);
    int arrive_count[g.size()] = {0};
    
    int current;
    while (q.size() > 0){

        current = q.front();
        for(auto neighboor : g[current]){
            arrive_count[neighboor]++;
        }
        q.erase(q.begin());
    }

    unordered_map<int, string> count_mapping;

    for(int i = 0; i<g.size(); i++){
        count_mapping[arrive_count[i]]+=(i+'a');
    }

    vector<string> cc;
    for(auto &[k, v]:count_mapping){
        cc.push_back(v);
    }

    sort(cc.begin(), cc.end(), less<string>());
    return cc;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;
    cin>>test_cases;

    int current_test_case=1;
    for (int i = 0; i < test_cases; i++){
        vector<vector<int>> graph = []{
            int vertex, edges;

            cin>>vertex>>edges; 
            vector<vector<int>> t(vertex );
            char from, to;
            for(int i = 0; i < edges; i++){
                cin>>from>>to;
                t[from-'a'].push_back(to-'a');
                t[to-'a'].push_back(from-'a');
            }
            return t;
        }();

        vector<string> cc = extract_connected_components(graph);

        cout<<"Case #"<<current_test_case<<":\n";
        for(auto component:cc){
            for(auto c:component){
                cout<<c<<",";
            }
            cout<<"\n";
        }
        cout<<cc.size()<<" connected components\n\n";
        current_test_case++;
    }
    cout.flush();

}