#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


void simulate_contamination(vector<vector<char>>& m){
    queue<pair<int, int>> q;
    vector<vector<int>> visited(m.size(), vector<int>(m[0].size(), 0));
    q.push({0,0});
    visited[0][0]=true;

    pair<int, int> current, neighboor;
    int rows=m.size();
    int columns=m[0].size();

    auto propagate_neighboor = [&]{
        if (
            neighboor.first >= rows or
            neighboor.second >= columns or
            neighboor.first < 0 or
            neighboor.second < 0
        ){
            return;
        }

        bool already_in_queue=false;
        if (not visited[neighboor.first][neighboor.second]){
            q.push(neighboor);
            already_in_queue=true;
            visited[neighboor.first][neighboor.second]=true;
        }

        if (m[neighboor.first][neighboor.second]=='T')
            return;

        if (m[current.first][current.second] != 'T') 
            return;
        // when the if statement above is false, so we know the current is a contamined posititon

        if (m[neighboor.first][neighboor.second] == 'X')
            return;

        if (m[neighboor.first][neighboor.second] != 'T' and not already_in_queue){
            q.push(neighboor); // we should visited the new contamined vertex again to make sure the contamination will be propagated
            visited[neighboor.first][neighboor.second]=true;
        }
        m[neighboor.first][neighboor.second]='T';
        
        if (not visited[neighboor.first][neighboor.second]){
            q.push(neighboor);
        } 
        
    };
    while (not q.empty()){

        current=q.front();

        neighboor={current.first+1, current.second};
        propagate_neighboor();
    
        neighboor={current.first, current.second+1};
        propagate_neighboor();
            
        neighboor={current.first-1, current.second};
        propagate_neighboor();
            
        neighboor={current.first, current.second-1};
        propagate_neighboor();

        q.pop();
        

    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int rows, columns;
    pair<int, int> first_contamined;



    cin>>rows>>columns;
    while (rows != 0){
        vector<vector<char>> m = [&]{
            vector<vector<char>> t(rows, vector<char> (columns));

            char current;
            for(int i = 0; i < rows*columns; i++){
                cin>>current;
                t[i/columns][i%columns]=current;
            }
            return t;

        }();
    
        simulate_contamination(m);

        for(auto r:m){
            for(auto c:r){
                cout<<c;
            }
            cout<<"\n";
        }
        cout<<"\n";

        cin>>rows>>columns;
    }


    cout.flush();

}