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

    string exp;
    unordered_map<char, double> notes_to_duration=[] {
        char notes[7]={'W', 'H', 'Q', 'E', 'S', 'T', 'X'};
        unordered_map<char, double> note_to_duration;
        for(int i = 0; i<7; i++){
            note_to_duration[notes[i]]=pow(2, -i);
        }
        return note_to_duration;
    }();

    getline(cin, exp);
    while(exp!="*"){
        double current_sum=0;
        int how_many_corrects=0;
        for(auto c:exp){
            if (c=='/'){
                how_many_corrects+=(current_sum==1.0);
                current_sum=0;
                continue;
            }
            current_sum+=notes_to_duration[c];
        }

        cout<<how_many_corrects<<"\n";

        cin>>exp;
    }

    cout.flush();

}