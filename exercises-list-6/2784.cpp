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


using Graph = vector<vector<pair<ll, int>>>;


vector<ll> dkjstra(Graph& g, int source){

    vector<ll> dists(g.size(), INF_LL);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> p;
    p.push({0, source});
    dists[source] = 0;

    while(not p.empty()){
        auto [dcurrent, current] = p.top();
        p.pop();
        
        if (dists[current] < dcurrent) continue;

        for(auto &[dneighboor, neighboor]:g[current]){
            if (dists[neighboor] < dneighboor + dcurrent) continue;

            dists[neighboor] = dneighboor + dcurrent;
            p.push({dists[neighboor], neighboor});
        }
    }
    return dists;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    Graph g = [](){
        int vertex, edges;
        cin>>vertex>>edges;
        Graph t(vertex);

        int from, to, weight;

        for(int i = 0; i < edges; i++){
            cin>>from>>to>>weight;

            t[from-1].push_back({weight, to-1});
            t[to-1].push_back({weight, from-1});
        }
        return t;
    }();


    int source;

    cin>>source;

    auto lesser_distances = dkjstra(g, source-1);
    auto biggest_ping = max_element(all(lesser_distances));
    lesser_distances[source-1]=*biggest_ping;
    auto least_ping = min_element(all(lesser_distances));

    cout<<*biggest_ping - *least_ping<<"\n";



    return 0;
}