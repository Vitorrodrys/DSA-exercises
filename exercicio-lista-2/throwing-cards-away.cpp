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

    int current_input;

    cin>>current_input;
    while(current_input!=0){

        deque<int> cards_deque(current_input);
        iota(cards_deque.begin(), cards_deque.end(), 1);

        deque<int> throwed_away_seq;
        while (cards_deque.size() > 1){

            throwed_away_seq.push_back(cards_deque.front());
            cards_deque.pop_front();

            cards_deque.push_back(cards_deque.front());
            cards_deque.pop_front();
        }

        cout<<"Discarded cards: ";
        for(auto it = throwed_away_seq.begin(); it != throwed_away_seq.end()-1; it++){
            cout<<*it<<", ";
        }
        cout<<throwed_away_seq.back();

        cout<<"\nRemaining card: "<<cards_deque.front()<<"\n";

        cin>>current_input;
    }


    cout.flush();

}