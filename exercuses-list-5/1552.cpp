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

struct Edge {
    int from;
    int to;
    double weight;
};

struct Graph{
    vector<Edge> e;
    size_t size;
};

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

double kruskal(Graph& g){

    auto &edges = g.e;
    sort(all(edges), [](auto v1, auto v2){return v1.weight < v2.weight;});

    UnionFind uf(g.size);
    
    double total_weight=0;
    for(auto &[from, to, w] : edges){

        if( uf.find(from) == uf.find(to) ) continue;

        uf.union_elements(from, to);
        total_weight+=w;
    }
    return total_weight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int people;

    int x_coord, y_coord, range;

    int queries;
    int qfrom, qto;
    double r;

    int test_cases;
    cin>>test_cases;
    for(int i = 0; i<test_cases; i++){

        cin>>people;
        Graph g = [&](){
            int x_coord, y_coord;
            vector<pair<int, int>> coords;
            coords.reserve(people);
            for(int i = 0; i < people; i++){
                cin>>x_coord>>y_coord;

                coords.push_back({x_coord, y_coord});
            }

            vector<Edge> edges;
            for(int i = 0; i < coords.size(); i++){
                for(int j = 0; j < i; j++){

                    auto &[xi_coord, yi_coord] = coords[i];
                    auto &[xj_coord, yj_coord] = coords[j];

                    double dist_between = sqrt(pow(xj_coord - xi_coord, 2) + pow(yj_coord-yi_coord, 2));

                    edges.push_back({i, j, dist_between});
                    edges.push_back({j, i, dist_between});
                }
            }
            return Graph{edges, (size_t)people};
        }();

        double r = kruskal(g)/100;

        std::cout << std::fixed << std::setprecision(2)<<r<<"\n";
    }
    return 0;
}