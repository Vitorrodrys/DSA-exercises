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

    int quantity_op;

    cin >> quantity_op;

    stack<int> gift_stack;
    stack<int> smallesties;

    int current;
    string op;

    for(int i = 0; i< quantity_op; i++){

        cin>>op;
        if (op == "PUSH"){
            cin>>current;
            gift_stack.push(current);
            if (!smallesties.empty() and current > smallesties.top()){
                continue;
            }
            smallesties.push(current);
            continue;
        }
        if (op == "MIN"){
            if (gift_stack.empty()){
                cout<<"EMPTY\n";
                continue;
            }
            cout<<smallesties.top()<<endl;
            continue;
        }
        if (op == "POP"){
            if (gift_stack.empty()){
                cout<<"EMPTY\n";
                continue;
            }
            current = gift_stack.top();
            gift_stack.pop();
            if (current == smallesties.top()){
                smallesties.pop();
            }
            continue;
        }
    
        
    


    }

    cout.flush();

}