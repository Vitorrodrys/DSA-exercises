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



using Graph = vector<tuple<int, int, int>>;
using GraphAdj = vector<vector<pair<int, int>>>;



class UnionFind {
    public:
        vector<int> parent;
        vector<int> rank;

        explicit UnionFind(int elements) : 
            parent(elements), rank(elements, 0)
        {
            iota(all(parent), 0);
        }

        int find(int e){
            if (parent[e] == e){
                return e;
            }
            return parent[e] = find(parent[e]);
        }
        void union_elements(int e1, int e2){
            int find_e1 = find(e1);
            int find_e2 = find(e2);
            if (find_e1 == find_e2) return;

            if (rank[find_e1] > rank[find_e2]){
                parent[find_e2] = find_e1;
            } else if (rank[find_e1] < rank[find_e2]){
                parent[find_e1] = find_e2;
            } else {
                parent[find_e1] = find_e2;
                rank[find_e1]++;
            }
        }
};


GraphAdj kruskal(Graph& g, int n){

    sort(all(g), [&](auto v1, auto v2){
        auto [f1, t1, v1_weight] = v1;
        auto [f2, t2, v2_weight] = v2;
        return v1_weight > v2_weight;
    });

    UnionFind uf(n);

    GraphAdj newg(n);
    for(auto [from, to, weight]:g){
        if (uf.find(from) == uf.find(to)) continue;

        uf.union_elements(from, to);
        newg[from].push_back({to, weight});
        newg[to].push_back({from, weight});
    }
    return newg;
}


class LCA{
    private:
        int levels;
        vector<vector<int>> parent;
        vector<vector<int>> minEdgVal;
        vector<int> depth;

        void dfs(GraphAdj& g, int c, int previous){
            parent[c][0] = previous;
            depth[c] = depth[previous]+1;
            for(auto [to, weight] : g[c]){
                if (parent[to][0] != -1) continue;

                minEdgVal[to][0] = weight; 
                dfs(g, to, c);
            }
        }

        void pre_calc_parent_table(GraphAdj& g){
            int ancestor;
            for(int level=1; level < levels; level++){
                for(int node = 0; node < g.size(); node++){
                    ancestor = parent[node][level-1];
                    if (ancestor != -1){
                        parent[node][level] = parent[ancestor][level-1];
                        minEdgVal[node][level] = min(minEdgVal[ancestor][ level-1 ], minEdgVal[node][level-1]);
                    }
                }
            }

        }
    
    public:

        explicit LCA(GraphAdj& g) : 
            levels(ceil(log2(g.size())) + 1),
            parent(g.size(), vector<int>(levels, -1)),
            minEdgVal(g.size(), vector<int>(levels, INF_INT)),
            depth(g.size(), -1)
        {
            dfs(g, 0, 0);
            pre_calc_parent_table(g);
        }

        int query_min_edge(GraphAdj& g, int a, int b){
            if ( depth[a] < depth[b] ){
                swap(a, b);
            }

            int min_edge = minEdgVal[a][0];
            int diff = depth[a] - depth[b];
            for(int i = 0; i < levels; i++){
                if ((diff>>i&1)){
                    min_edge = min(min_edge, minEdgVal[a][i]);
                    a = parent[a][i];
                }
            }

            if (a == b){
               return min_edge;
            }

            min_edge = min(min_edge, minEdgVal[b][0]);
            for(int i = levels-1; i >= 0; i--){
                if (parent[a][i] != parent[b][i]){
                    min_edge = min(min_edge, minEdgVal[a][i]);
                    min_edge = min(min_edge, minEdgVal[b][i]);

                    a=parent[a][i];
                    b=parent[b][i];
                }
            }
            return min({min_edge, minEdgVal[a][0], minEdgVal[b][0]});
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertices, edges, questions;


    int from, to;
    while (cin>>vertices>>edges>>questions){

        Graph g = [&](){
            Graph t;
            int from, to, weight;
            for(int i = 0; i < edges; i++){
                cin>>from>>to>>weight;
                t.push_back({from-1, to-1, weight});
            }
            return t;
        }();

        GraphAdj agm = kruskal(g, vertices);

        LCA lca_calc(agm);

        for(int i = 0; i < questions; i++){
            cin>>from>>to;

            cout<<lca_calc.query_min_edge(agm, from-1, to-1)<<"\n";
        }
    }


    return 0;
}