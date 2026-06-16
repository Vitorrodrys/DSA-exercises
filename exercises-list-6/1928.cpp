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

using Graph = vector<vector<int>>;


class LCA {

    private:
    int levels;
    vector<int> depth;
    vector<vector<int>> parent;

    void dfs(Graph& g, int current, int prev){
        depth[current] = depth[prev]+1;
        parent[current][0] = prev;
        for(auto neighboor:g[current]){
            if (parent[neighboor][0] != -1) continue;

            dfs(g, neighboor, current);
        }

    }

    void compute_lca_matrix(int n){
        for(int node = 0; node < n; node++){
            for( int l = 1; l < levels; l++){
                if (parent[node][l-1] != -1)
                    parent[node][l] = parent[parent[node][l-1]][l-1];
            }
        }
    }
    public:
    explicit LCA(Graph& g) : levels(ceil(log2(g.size())) + 1), parent(g.size(), vector<int>(levels, -1)), depth(g.size(), 0){
        int source = 0;
        for(; source < g.size(); source++){
            if ( parent[source][0] != -1 ) continue;

            depth[source] = -1; // ensure that depth of the root is 0
            dfs(g, source, source); // first parent of source is itself
        }
        compute_lca_matrix(g.size());
    }

    int query_lca(int a, int b){

        if (depth[a] < depth[b]){
            swap(a, b);
        }

        int diff = depth[a] - depth[b];
        for(int l = 0; l < levels; l++){
            if ( (diff>>l) & 1 ){
                a = parent[a][l];
            }
        }

        if (a == b){
            return a;
        }

        for(int i = levels-1; i >= 0; i--){
            if (parent[a][i] != parent[b][i]){
                a = parent[a][i];
                b = parent[b][i];
            }
        }
        return parent[a][0];
    }


    int calc_height_diff(int a, int b){
        return abs(depth[a] - depth[b]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int letters;
    cin>>letters;
    vector<pair<int, int>> chart_pairs(letters, {-1, -1});

    int index;
    for(int i = 0; i < letters; i++){
        cin>>index;
        index--;
        if (chart_pairs[index].first == -1){
            chart_pairs[index].first = i;
        }else{
            chart_pairs[index].second = i;
        }
    }

    Graph g = [&](){
        Graph t(letters);
        int from, to;
        for(int i = 0; i < letters-1; i++){
            cin>>from>>to;
            t[from-1].push_back(to-1);
            t[to-1].push_back(from-1);
        }
        return t;
    }();


    LCA lca_calculator(g);
    g.clear();
    int sum = 0;
    for(auto chart_pair:chart_pairs){
        if (chart_pair.first == -1 or chart_pair.second == -1) continue;

        int lca = lca_calculator.query_lca(chart_pair.first, chart_pair.second);
        sum+=lca_calculator.calc_height_diff(chart_pair.first, lca) + lca_calculator.calc_height_diff(chart_pair.second, lca);
    }

    cout<<sum<<"\n";

    return 0;
}