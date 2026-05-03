#include <bits/stdc++.h>
#include <cstdint>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>


using namespace std;



int calculate_pen_movements(vector<vector<uint8_t>>& g, int starting_from){

    stack<uint8_t> s;
    vector<uint8_t> visisted(g.size());
    s.push(starting_from);

    int movements=0;
    int current;
    int last_popped = 0;
    int neighboor;
    do{

        current = s.top();
        visisted[current] = true;
        auto it=g[current].begin()+last_popped;
        for(; it != g[current].end(); it++){

            if (not *it) continue; // edge does not exists

            neighboor = it-g[current].begin();
            if (visisted[neighboor]) continue;
            movements++;
            s.push(neighboor);
            last_popped=0;//we should clear the previous last_popped value when going deeper to prevent old values from skipping nodes unintentionally
            break;
        }
        if (g[current].end() == it){
            last_popped=s.top();
            s.pop();
            movements++;
        }
    }while(not s.empty());

    // we should return movemnts - 1 to not count the back pencil movement to the starting point vertex.
    return movements-1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int test_cases;
    int starting_from;
    int qnodes, qedges;

    cin>>test_cases;

    for(int i = 0; i<test_cases; i++){

        cin>>starting_from;
        cin>>qnodes>>qedges;
        vector<vector<uint8_t>> graph = [&]{
            vector<vector<uint8_t>> t(qnodes);
            for(int i = 0; i<qnodes; i++){
                t[i].resize(qnodes);
            }
            int from, to;
            for(int i = 0; i<qedges; i++){
                cin>>from>>to;
                if (t[from][to]) continue;
                t[from][to]=true;
                t[to][from]=true;
            }
            return t;
        }();
        cout<<calculate_pen_movements(graph, starting_from)<<"\n";

    }
    cout.flush();

}