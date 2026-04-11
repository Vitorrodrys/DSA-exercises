


#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void process_most_frequency(set<char>& most_frequency_chars){

    vector<char> as_vector(most_frequency_chars.begin(), most_frequency_chars.end());

    sort(as_vector.begin(), as_vector.end());

    for(auto current:as_vector){
        cout<<current;
    }
    cout<<endl;
}

void get_most_frequency(string& current_line){

    unordered_map<char, int> count_mapping;
    unordered_map<int, set<char>> count_to_char;

    int most_frequency_one_counting=0;

    int current_count;
    char current_char;
    for(auto it = current_line.begin(); current_line.end() != it; it++){

        if (!isalpha(*it)){
            continue;
        }
        current_char=tolower(*it);
        current_count = count_mapping[current_char];

        count_to_char[current_count].erase(current_char);

        current_count++;
        count_mapping[current_char]=current_count;
        count_to_char[current_count].insert(current_char);

        if (most_frequency_one_counting< current_count){
            most_frequency_one_counting=current_count;
        }
    }
    process_most_frequency(count_to_char[most_frequency_one_counting]);

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test_cases;

    cin >> test_cases;
    cin.ignore();

    string current_line;

    for (int i = 0; i<test_cases; i++){

        getline(cin, current_line);
        get_most_frequency(current_line);
        
    }

    cout.flush();

}