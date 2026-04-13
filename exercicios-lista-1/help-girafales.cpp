#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


bool check_different(const string& o1, const string& o2){
    int difference=0;
    for(int i = 0; i<o1.size(); i++){
        if (o1[i] != o2[i]){
            difference++;
        }
        if (difference > 1){
            return true;
        }
    }
    return false;
}

void check_signatures(unordered_map<string, string>& student_to_sign, int quantity_to_check){
    string student_name, to_check;
    int false_sign_count=0;
    for(int i = 0; i<quantity_to_check; i++){
        cin>>student_name;
        cin>>to_check;

        if (check_different(student_to_sign[student_name], to_check)){
            false_sign_count++;
        }
    }
    cout<<false_sign_count<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int quantity_students, quantity_to_check;
    cin>>quantity_students;

    unordered_map<string, string> student_to_sign;

    string student, sign;


    while (quantity_students){
        for (int i = 0; i<quantity_students; i++){
            cin >> student;
            cin >> sign;

            student_to_sign[student] = sign;
        }
        cin>>quantity_to_check;
        check_signatures(student_to_sign, quantity_to_check);
        cin>>quantity_students;
    }


    cout.flush();

}