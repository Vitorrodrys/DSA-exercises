#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <numeric>
using namespace std;



int find_remaining(long int n, long int a, long int b){
    unordered_map<long int, long int> soldier_count;
    soldier_count.reserve(n/10000);

    long int remaining=n;
    long int index_to_kill=0;
    while(remaining>0){
        // index_to_kill = ((a*index_to_kill*index_to_kill)+b)%n
        index_to_kill=(
            ( ( a % n ) * ( index_to_kill%n * index_to_kill%n ) % n ) % n + b % n 
        ) % n;
        soldier_count[index_to_kill]++;
        if (soldier_count[index_to_kill] == 2){
            remaining--;
        }else if (soldier_count[index_to_kill] == 3){
            break;
        }
    }
    return remaining;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long int n, a, b;

    vector<bool> a = {true, false, true};

    auto x = a[0];
    cin>>n;
    while (n){
        cin>>a>>b;
        cout<<find_remaining(n, a, b)<<"\n";
        cin>>n;;
    }
    cout.flush();

}