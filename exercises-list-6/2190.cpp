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


using Graph = vector<array<int, 3>>;

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


Graph kruskal(Graph& g){

    UnionFind uf(g.size()+1);

    sort(all(g));
    Graph n;
    for(auto &[weight, from, to]:g){
        if (uf.find(from) == uf.find(to))
            continue;

        uf.union_elements(from, to);
        n.push_back({weight, from, to});
    }
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int vertex, edges;

    cin>>vertex>>edges;

    int test_case=1;
    while (vertex != 0){
        Graph g = [&](){
            int from, to, weight;

            Graph t;
            t.reserve(edges);
            for(int i = 0; i < edges; i++){
                cin>>from>>to>>weight;
                t.push_back({weight, from, to});
            }
            return t;
        }();

        Graph mst = kruskal(g);

        cout<<"Teste "<<test_case<<"\n";
        for(auto &[_, from, to]:mst){
            if (from < to){
                cout<<from<<" "<<to<<"\n";
            }else{
                cout<<to<<" "<<from<<"\n";
            }
        }
        cout<<"\n";
        test_case++;
        cin>>vertex>>edges;
    }
    return 0;
}