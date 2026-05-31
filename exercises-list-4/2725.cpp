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
            parent(elements), rank(elements, 1)
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
            parent[find_e2] = find_e1;


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
    int wires_amount=0;
    for(auto next:g.edges){
        if (uf.find(next.from) == uf.find(next.to)) continue;

        mst_g.edges.push_back(next);
        uf.union_elements(next.from, next.to);
        uf.union_elements(next.to, next.from);
        wires_amount+=next.weight;
    }

    return wires_amount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int test_cases;
    int vertices, fee_rate;

    cin>>test_cases;


    for(auto i:views::iota(0, test_cases)){

        cin>>vertices>>fee_rate;

        auto g =[&](){
            vector<Edge> e;
            e.reserve(vertices*vertices);
            int bytelandian_amount=0;

            vector<pair<int, int>> cords;
            int from, to;
            for(auto i:views::iota(0, vertices)){
                cin>>from>>to;
                cords.push_back({from, to});
            }

            for(int i=0; auto c1:cords){
                for(int j=0; auto c2:cords){

                    auto dx = abs(c1.first-c2.first);
                    auto dy = abs(c1.second-c2.second);
                    if (i!=j){
                        e.push_back(
                            Edge{
                                .from=i,
                                .to=j,
                                .weight=(gcd(dx, dy)-1)*fee_rate
                            }
                        );
                    }
                    j++;
                }
                i++;
            }
            return Graph{vertices, e};
        }();

        cout<<kruskal(g)<<"\n";
    }
}