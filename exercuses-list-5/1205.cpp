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

vector<ll> dkjstra(int source, Graph& g, unordered_map<int, ll>& m){
    
    vector<ll> dists(g.size(), INF_LL);

    dists[source]=m[source];
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push({m[source], source});

    while(not q.empty()){
        auto [d, c] = q.top();
        q.pop();
        
        if (d > dists[c]) continue;

        for(auto n:g[c]){

            ll nd = m[n]; // how many have to kill to cross the edge c to n

            if (dists[n] > dists[c] + nd){
                dists[n] = dists[c] + nd;
                q.push({dists[n], n});
            }
        }
    }
    return dists;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int vertices, edges, sooldier_bullets;

    double kill_prob;

    while (cin>>vertices>>edges>>sooldier_bullets>>kill_prob){


        Graph g = [&](){

            Graph t(vertices, vector<int>(0));

            for(int i = 0; i < edges; i++){
                int from, to;
                cin>>from>>to;
                t[from-1].push_back(to-1);
                t[to-1].push_back(from-1);
            }
            return t;
        }();
        
        unordered_map<int, ll> m = [&](){
            int a;
            cin>>a;

            int coord;
            unordered_map<int, ll> m;
            for(int i = 0; i < a; i++){
                cin>>coord;
                m[coord-1]++;
            }
            return m;
        }();

        int leaving_from, coming_to;
        cin>>leaving_from>>coming_to;
        ll dist = dkjstra(leaving_from-1, g, m)[coming_to-1];
        if (((ll)sooldier_bullets) < dist){
            cout<<"0.000\n";
            continue;
        }
        double r = pow(kill_prob, dist);
        cout << fixed << setprecision(3) << r << "\n";
    }

    return 0;
}