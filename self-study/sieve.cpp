#include <bits/stdc++.h>
using namespace std;
using namespace ranges;

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


vector<ll> sieve(ll n){

    vector<int> factors(n+1, 0);

    for(ll d = 2; d<=n; d++){

        if (factors[d] != 0) continue;

        for(ll mult=d*2; mult <= n; mult+=d){
            factors[mult]++;
        }
    }

    return views::zip(views::iota(0), factors)
    | views::filter([](auto pair) {
        auto [idx, value] = pair;
        return value == 0 and idx!=0 and idx!=1;
      })
    | views::transform([](auto pair) {
        auto [idx, value] = pair;
        return idx;
      })
    | std::ranges::to<std::vector<ll>>();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ll> primes_in_range = sieve(100000000);
    for(auto p:primes_in_range){
        cout<<p<<"\n";
    }
    return 0;
}