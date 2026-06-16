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


class Graph {
    public:
        vector<vector<pair<int, int>>> g;
        vector<vector<int>> reachability;

    public:
        Graph(int size){
            g = vector<vector<pair<int, int>>>(size, vector<pair<int, int>>());
            reachability=vector<vector<int>>(size, vector<int>(0));
            int row = 0;
            generate(all(reachability), [&row](){
                row++;
                return vector<int>(row, 0);
            });
        }

        void add(int from, int to, int weight){
            from = from -1;
            to = to-1;
            g[from].push_back({to, weight});
            if (from > to){
                reachability[from][to]++;
            }else{
                reachability[to][from]++;
            }
        }
        bool is_connected(int from, int to){
            if (from < to) {
                swap(from, to);
            }
            assert (reachability[from][to]<=2);
            return reachability[from][to] == 2;
        }

        size_t size(){
            return g.size();
        }
};


vector<ll> dkjstra(int source, Graph& g){

    vector<ll> dists(g.size(), INF_LL);

    dists[source]=0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, source});

    pair<int, int> current;
    while (not q.empty()){
        current = q.top(); q.pop();
        auto [current_dist, current_idx] = current;

        if (current_dist > dists[current_idx]) continue;

        for(auto [neighbor_idx, neighbor_distance]:g.g[current_idx]){

            if (g.is_connected(current_idx, neighbor_idx)){
                neighbor_distance = 0;
            }

            if (dists[neighbor_idx] > dists[current_idx] + neighbor_distance){
                dists[neighbor_idx] = dists[current_idx] + neighbor_distance;
                q.push({dists[neighbor_idx], neighbor_idx});
            }
        }
    }
    return dists;
}

class LookUpDistTable {

    private:
        unordered_map<int, vector<ll>> t;
        Graph& g;

    public:
        explicit LookUpDistTable(Graph& g) : g(g){}

        ll get_dist(int from, int to){
            from = from -1;
            to = to - 1;
            if (t.count(from) == 0){
                t[from] = dkjstra(from, g);
            }
            return t[from][to];
        }

};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int vertices, edges;

    cin>>vertices>>edges;

    int queries;
    int from_q, to_q;
    ll dist;
    while(vertices != 0){
        Graph g = [&](){
            int from, to, weight;

            Graph g = Graph(vertices+1);
            for(int i = 0; i<edges; i++){
                cin>>from>>to>>weight;
                g.add(from, to, weight);
            }
            return g;
        }();

        LookUpDistTable t = LookUpDistTable(g);

        cin>>queries;

        for(int i = 0; i<queries; i++){

            cin>>from_q>>to_q;
            dist = t.get_dist(from_q, to_q);
            if (dist == INF_LL){
                cout<<"Nao e possivel entregar a carta";
            } else {
                cout<<dist;
            }
            cout<<"\n";
        }
        cout<<"\n";

        cin >>vertices>>edges;
    }



    return 0;
}