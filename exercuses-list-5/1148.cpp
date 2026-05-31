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


vector<ll> dkjstra(int source, Graph& g){

    vector<ll> dists(g.size(), INF_LL);

    dists[source]=0;
    vector<char> visited(g.size(), 0);
    priority_queue<pair<int, int>> q;
    q.push({source, 0});

    pair<int, int> current;
    int neighboor;
    int neighboor_distance;
    while (not q.empty()){
        current = q.top(); q.pop();
        for(auto it=g[current.first].begin(); it!=g[current.first].end(); it++){
            
            neighboor = it-g[current.first].begin();
            neighboor_distance = *it;
            if (visited[neighboor] or *it == 0 or neighboor == current.first) continue;

            
            q.push({neighboor, *it});
            visited[neighboor]=true;

            if (dists[neighboor] > dists[current.first] + neighboor_distance){
                dists[neighboor] = dists[current.first] + neighboor_distance;
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
    int dist;
    while(vertices != 0){
        Graph g = [&](){
            int from, to, weight;

            Graph g = Graph(vertices+1, vector<int>(vertices+1, 0));
            for(int i = 0; i<edges; i++){
                cin>>from>>to>>weight;
                g[from][to]=weight;
            }
            return g;
        }();

        LookUpDistTable t = LookUpDistTable(g);

        cin>>queries;

        for(int i = 0; i<queries; i++){

            cin>>from_q>>to_q;
            dist = t.get_dist(from_q, to_q);
            if (dist == INF_LL){
                cout<<" Nao e possivel entregar a carta";
            } else {
                cout<<dist;
            }
            cout<<"\n";
        }
        cout<<"\n";
    }



    return 0;
}