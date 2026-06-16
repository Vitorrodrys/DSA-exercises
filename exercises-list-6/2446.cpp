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


/*
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int value, kinds;

    cin>>value>>kinds;
    vector<int> coin_values(kinds, 0);

    for(int i = 0; i < kinds; i++){
        cin>>coin_values[i];
    }


    vector<vector<int>> dp(kinds + 1, vector<int>(value+1, 0));

    dp[0][0] = 1;
    int current_coin;
    for (int i = 1; i <= kinds; i++){
        for(int j = 0; j <=value; j++){

            dp[i][j] += dp[i-1][j];

            if (j - coin_values[i-1] >= 0){
                dp[i][j] += dp[i-1][j-coin_values[i-1]];
            }
        }
    }

    if (dp[kinds][value] > 0){
        cout<<"S\n";
    }else{
        cout<<"N\n";
    }
    return 0;
}
    */


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sum, coin_kinds;

    cin>>sum>>coin_kinds;

    vector<int> coin_values(coin_kinds, 0);

    for(int i = 0; i < coin_kinds; i++){
        cin>>coin_values[i];
    }

    vector<char> dp(sum+1, false);
    dp[0]=true;
    for(auto coin:coin_values){
        for(int j = sum; j >= coin; j--){
            if (dp[j-coin])
                dp[j] = dp[j-coin];
        }
    }

    if (dp[sum]){
        cout<<"S\n";
    }else{
        cout<<"N\n";
    }
}