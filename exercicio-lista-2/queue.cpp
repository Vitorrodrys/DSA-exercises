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

    int size_queue;

    int quantity_remove;
    int to_remove;
    int index_to_remove;

    int ident_to_index[100000+1] = {0};
    cin>>size_queue;

    int current_ident;

    vector<pair<int, bool>> ident_queue;
    ident_queue.reserve(size_queue);

    for(int i = 0; i<size_queue; i++){
        cin>>current_ident;
        ident_to_index[current_ident]=i;
        ident_queue.push_back(pair(current_ident, true));
    }

    cin>>quantity_remove;
    for(int i = 0; i < quantity_remove; i++){
        cin>>to_remove;
        index_to_remove=ident_to_index[to_remove];
        ident_queue[index_to_remove].second = false;
    }

    auto it= ident_queue.begin();
    for(; it != ident_queue.end(); it++){
        if ((*it).second){
            cout<<(*it).first;
            break;
        }
    }
    for(it++; it != ident_queue.end(); it++){
        if ((*it).second){
            cout<<" "<<(*it).first;
        } 
    }
    cout<<"\n";

    cout.flush();

}