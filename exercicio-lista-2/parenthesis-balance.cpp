#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


bool check(const string& exp){

    int count=0;
    for(auto c:exp){
        if (c=='('){
            count++;
        }else if(c==')'){
            count--;
        }

        if (count < 0){
            return false;
        }
    }
    return count==0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    string exp;

    while( getline(cin, exp) ){
        cout<<(check(exp)?"correct\n":"incorrect\n");
    }
    cout.flush();

}