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


using Graph = vector<vector<pair<int, int>>>;



#define NOT_VISISTED -2

class SCCS{

    private:
        vector<int> sccs;
        int sccs_ident=0;
    
        int timer;
        void tarjan(Graph& g, int current, stack<int>& s, vector<char>& inSt, vector<int>& low, vector<int>& tin){
            tin[current] = low[current] = timer++;
            s.push(current);
            inSt[current]=true;
            for(auto neighbor:g[current]){
                auto [neighbor_idx, neighbor_dist] = neighbor;

                if (tin[neighbor_idx] == NOT_VISISTED ){
                    tarjan(g, neighbor_idx, s, inSt, low, tin);
                    low[current] = min(low[current], low[neighbor_idx]);
                }else if(inSt[neighbor_idx]){
                    low[current] = min(low[current], tin[neighbor_idx]);
                }
            }

            if (low[current] == tin[current]){
                int x;
                do {
                    x = s.top();s.pop();
                    sccs[x] =  sccs_ident;
                    inSt[x] = false;
                }while(x!=current);

                sccs_ident++;
            }

            


        }
    public:
        explicit SCCS(Graph& g) {
            sccs.resize(g.size());
            timer=0;
            
            stack<int> s;
            vector<char> inSt(g.size(), false);
            vector<int> low(g.size(), NOT_VISISTED), tin(g.size(), NOT_VISISTED);
            for(int i = 0; i < tin.size(); i++){
                if (tin[i] == NOT_VISISTED)
                    tarjan(g, i, s, inSt, low, tin);
            }
        }

        bool check_connectivity(int from, int to){
            return sccs[from] == sccs[to];
        }

};