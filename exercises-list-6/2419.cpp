#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int INF_INT = 1e9 + 20; // evitar overflow
const ll INF_LL = 4e18 + 123; // evitar overflow
const int MOD = 1e9 + 7; // número primo grande


using Graph = vector<vector<char>>;


vector<pair<int, int>> get_neighboors(Graph& g, int x, int y){
    vector<pair<int, int>> neighboors;

    auto check_add = [&](int nx, int ny){
        int n = (int)g.size();
        if (nx >= -1 && ny >= -1 && nx <= n && ny <= n)
        {
            neighboors.push_back({nx, ny});
        }
    };

    check_add(x-1, y);
    check_add(x, y-1);
    check_add(x,   y+1);
    check_add(x+1, y);

    return neighboors;

}

#define VISISTED 'v'

bool is_out_of_map(Graph& g, int x, int y){
    return x < 0 or x >= g.size() or y < 0 or y >= g.size();
    
}

char get_v(Graph& g, int x, int y){
    if (x == -1 or x == g.size() or y == -1 or y == g.size() ){
        return '.';
    }
    return g[x][y];
}

bool has_sea_around(Graph& g, int x, int y){

    if (g[x][y] != '#') return false;

    for(auto [nx, ny]:get_neighboors(g, x, y)){
        if (get_v(g, nx, ny) == '.') return true;
    }
    return false;
}
/*
int compute(Graph& g){

    queue<pair<int, int>> q;
    q.push({0,0});

    int sea_cost=0;

    while (q.size()){
        auto [x, y] = q.front(); 
        q.pop();

        if (g[x][y] == VISISTED) continue;

        if (has_sea_around(g, x, y))
            sea_cost++;

        for(auto [xneighboor, yneighboor]:get_neighboors(g, x, y)){
            if (is_out_of_map(g, xneighboor, yneighboor)) continue;

            q.push({xneighboor, yneighboor});
        }
        g[x][y] = VISISTED;
    }
    return sea_cost;
}
*/

int compute(Graph& g){
    int sea_cost=0;
    for(int i = 0; i < g.size(); i++){
        for(int j = 0; j < g[0].size(); j++){
            if (has_sea_around(g, i, j)){
                sea_cost++;
            }
        }
    }
    return sea_cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int height, weigth;

    cin>>height>>weigth;

    
    Graph g = [&](){
        Graph t(height, vector<char>(weigth, 0));
        for(int i = 0; i < height; i++){
            for(int j = 0; j < weigth; j++){
                cin>>t[i][j];
            }
        }
        return t;
    }();

    int sea_cost = compute(g);

    cout<<sea_cost<<"\n";



    return 0;
}