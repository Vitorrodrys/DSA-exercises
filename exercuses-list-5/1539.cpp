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

using Graph = vector<vector<pair<int, double>>>;



vector<double> dkjstra(int source, Graph& g){

    vector<double> dists(g.size(), INF_LL);

    dists[source]=0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    q.push({0, source});

    pair<int, int> current;
    while (not q.empty()){
        current = q.top(); q.pop();
        auto [current_dist, current_idx] = current;

        if (current_dist > dists[current_idx]) continue;

        for(auto [neighbor_idx, neighbor_distance]:g[current_idx]){


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
        unordered_map<int, vector<double>> t;
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


    int antennas;

    int x_coord, y_coord, range;

    int queries;
    int qfrom, qto;
    double r;

    cin>>antennas;
    while (antennas != 0){

        Graph g = [&](){
            int x_coord, y_coord, range;
            vector<array<int, 3>> coords;
            coords.reserve(antennas);
            for(int i = 0; i < antennas; i++){
                cin>>x_coord>>y_coord>>range;

                coords.push_back({x_coord, y_coord, range});
            }

            Graph t(antennas, vector<pair<int, double>>());
            for(int i = 0; i < coords.size(); i++){
                for(int j = 0; j < coords.size(); j++){
                
                    if (i == j) continue;

                    auto &[xi_coord, yi_coord, irange] = coords[i];
                    auto &[xj_coord, yj_coord, _] = coords[j];

                    double dist_between = sqrt(pow(xj_coord - xi_coord, 2) + pow(yj_coord-yi_coord, 2));
                    if ( dist_between > irange ) continue;

                    t[i].push_back({j, dist_between});
                }
            }
            return t;
        }();

        cin>>queries;

        LookUpDistTable l(g);

        for(int i = 0; i < queries; i++){
            cin>>qfrom>>qto;
            r = l.get_dist(qfrom, qto);

            if ( r == INF_LL){
                cout<<"-1\n";
            } else {
                cout<<static_cast<int>(r)<<"\n";
            }
        }

        cin>>antennas;


    }
    return 0;
}