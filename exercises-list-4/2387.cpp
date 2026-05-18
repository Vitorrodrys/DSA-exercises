#include <bits/stdc++.h>
#include <ranges>

using namespace std;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int MOD = 1e9 + 7; // número primo grande


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int appointments;
    cin>>appointments;

    vector<pair<int, int>> appointments_vec;
    appointments_vec.reserve(appointments);

    pair<int, int> current;
    for(int i = 0; i < appointments; i++){
        cin>>current.first>>current.second;
        appointments_vec.push_back(current);
    }

    sort(all(appointments_vec), [](auto v1, auto v2){
        return (v1.first != v2.first and v1.first < v1.first) or v1.second < v2.second;
    });

    current=appointments_vec.front();
    int quantity=1;
    for(auto each:appointments_vec | views::drop(1)){

        if (each.first >= current.second ){
            quantity++;
            current=each;
        }
    }

    cout<<quantity<<"\n";


}