#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int MOD = 1e9 + 7; // número primo grande



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

struct Edge {
    int from;
    int to;
    int weight;
};

struct Graph {
    int size;
    vector<Edge> edges;
};


int kruskal(Graph& g){
    Graph mst_g = Graph{g.size, vector<Edge>()};

    sort(all(g.edges), [](auto e1, auto e2){
        return e1.weight < e2.weight;
    });

    UnionFind uf(g.size);
    int weight_sum=0;
    for(auto next:g.edges){
        if (uf.find(next.from) == uf.find(next.to)) continue;

        mst_g.edges.push_back(next);
        uf.union_elements(next.from, next.to);
        uf.union_elements(next.to, next.from);
        weight_sum+=next.weight;
    }

    return weight_sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int vertices, edges;

    cin>>vertices>>edges;

    auto g =[&](){
        vector<Edge> e;
        e.reserve(edges);

        int from, to, weight;
        for(auto i:views::iota(0, edges)){
            cin>>from>>to>>weight;

            e.push_back({from-1, to-1, weight});
        }
        return Graph{vertices, e};
    }();

    cout<<kruskal(g)<<"\n";
}