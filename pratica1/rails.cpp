#include <bits/stdc++.h>
#include <stack>
#include <optional>

using namespace std;


pair<vector<char>, bool> calculate_sequence(vector<char>& marshal_seq, vector<char>& target){
    stack<int> temp;
    int idx_tg = 0;
    vector<char> response_seq;
    for( auto current:marshal_seq){

        if ( current != target[idx_tg] ){
            temp.push(current);
            response_seq.push_back('I');
            continue;
        }

        idx_tg++;
        response_seq.push_back('I');
        response_seq.push_back('R');
        while (temp.size() > 0 and temp.top() == target[idx_tg]){
            temp.pop();
            response_seq.push_back('R');
            idx_tg++;
        }
    }
    return pair(response_seq, temp.empty());
}

vector<char> read_seq(int quantity){
    vector<char> coaches;
    char current;
    for(int i = 0; i<quantity; i++){
        cin>>current;
        coaches.push_back(current);
    }
    return coaches;
}

void check_train_coaches(int coaches_quantity){
    
    auto marshal_seq = read_seq(coaches_quantity);
    auto target_seq = read_seq(coaches_quantity);

    auto response = calculate_sequence(marshal_seq, target_seq);
    for(auto mov:response.first){
        cout<<mov;
    }
    if (!response.second){
        cout<<" Impossible";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int coaches_quantity;

    cin>>coaches_quantity;
    while(coaches_quantity){

        check_train_coaches(coaches_quantity);
        cout<<endl;
        cin >> coaches_quantity;
    }
    cout.flush();

}