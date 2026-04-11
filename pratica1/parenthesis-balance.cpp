#include <bits/stdc++.h>
#include <iostream>

using namespace std;

bool check(string expression){
    int parenthesis_count = 0;
    for(auto character:expression){
        if (character == '('){
            parenthesis_count++;
        }else if(character == ')'){
            parenthesis_count--;
        }
        if (parenthesis_count < 0){
            return false;
        }
    }
    return !parenthesis_count;
}

int main(){
    string current_expression;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin>>current_expression){
        cout << (check(current_expression)?"correct":"incorrect") << '\n';
    }
    cout.flush();

}