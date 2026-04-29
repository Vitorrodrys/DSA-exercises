#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int quantity_tests;
    cin>>quantity_tests;

    int from, quantity;
    for(int i = 0; i<quantity_tests; i++){

        cin>>from>>quantity;
        int nearest_odd_index= from/2;
        int to=nearest_odd_index+quantity;
        cout<<to*to-nearest_odd_index*nearest_odd_index<<"\n";
    }
    cout.flush();

}