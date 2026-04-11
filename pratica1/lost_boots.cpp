#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define POSSIBLE_BOOTS 61
#define UNSET (char)'\0'

void check_boots(int quantity_boots){
    pair<int, int> boots_mapping[POSSIBLE_BOOTS] = {};

    char current_boot_foot;
    int current_boot_size;

    int quantity_pair = 0;
    for(int i = 0; i<quantity_boots; i++){

        cin>>current_boot_size;
        cin>>current_boot_foot;

        if (current_boot_foot == 'D') {
            boots_mapping[current_boot_size].first++;
        }else{
            boots_mapping[current_boot_size].second++;
        }

    }
    for (pair<int, int> current:boots_mapping){
        quantity_pair+=min(current.first, current.second);
    }
    cout<<quantity_pair<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int quantity;
    
    while (cin >> quantity){
        check_boots(quantity);
    }


    cout.flush();

}