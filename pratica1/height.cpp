#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

vector<int> to_vector(string& cities_height){
    stringstream ss(cities_height);
    string token;
    vector<int> tokens;

    while(getline(ss, token, ' ')){
        tokens.push_back(stoi(token));
    }
    return tokens;
}

void process_city(){
    int people_among;
    string cities_height;

    cin>>people_among;
    cin.ignore();
    getline(cin, cities_height);
    vector<int> cities_heightv = to_vector(cities_height);

    sort(cities_heightv.begin(),cities_heightv.end());

    cout<<cities_heightv[0];
    for(auto it=cities_heightv.begin()+1;cities_heightv.end()!=it; it++){
        cout<<" "<<*it;
    }
    cout<<endl;
}

void process_input_case(int quantity_cities){
    for(int i = 0; i < quantity_cities; i++){
        process_city();
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int iquantity;

    while(cin>>iquantity){
        cin.ignore();
        process_input_case(iquantity);
    }

    cout.flush();

}