/**
 *  beecrowd | 1077 
 *  Infix to Posfix
 */

#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>
#include <assert.h>

using namespace std;

/*
Grammar:

SUM: MULT + MULT SUM | MULT - MULT SUM | LAMBDA
MULT: POT * LEAF MULT | POT / LEAF MULT | LAMBDA
POT: LEAF ^ LEAF POT | LAMBDA
LEAF: (EXP) | token | number

*/

const set<char> ops = {'+', '-', '*', '/', '^'};

inline bool is_op(char s){
    return ops.find(s) != ops.end();
}

pair<string, int> sum(const string& exp, int start_index);
pair<string, int> mult(const string& exp, int start_index);
pair<string, int> pot(const string& exp, int start_index);
pair<string, int> leaf(const string& exp, int start_index);

pair<string, int> sum(const string& exp, int start_index){

    string result_posfix = "";
    int amount_proceed = 0;

    const set<char> sum_operators = {'+', '-'};

    const auto is_sum_op = [&sum_operators](char c){
        return sum_operators.find(c) != sum_operators.end();
    };

    pair result_l = mult(exp, start_index);
    start_index+=result_l.second;

    if (start_index == exp.size() or exp[start_index] == ')' ){
        // enf of an expression, we can return it safely
        // Note: the leaf expression will increment the index to the ')' caracter
        return pair(
            result_posfix + result_l.first,
            amount_proceed + result_l.second
        );
    }

    if (start_index < exp.size() and not is_op(exp[start_index])){
        throw invalid_argument("exp start index is expected to be an operator. However, it's not: " + exp[start_index]);
    }

    if (not is_sum_op(exp[start_index])){
        return pair(
            result_posfix + result_l.first,
            amount_proceed + result_l.second
        );
    }
    amount_proceed+=result_l.second;
    result_posfix=result_l.first;
    do{
        pair result_r = mult(exp, start_index+1);
        result_posfix+=result_r.first + exp[start_index];
        start_index+=result_r.second;
        amount_proceed+=result_r.second+1; // adding 1 because of the operand
        start_index++;
    } while (is_sum_op(exp[start_index]) and exp[start_index] != ')' and start_index < exp.size());

    return pair(result_posfix, amount_proceed);
}

pair<string, int> mult(const string& exp, int start_index){

    string result_posfix = "";
    int amount_proceed = 0;

    const set<char> mult_operators = {'*', '/'};

    const auto is_mult_op = [&mult_operators](char c){
        return mult_operators.find(c) != mult_operators.end();
    };

    pair result_l = pot(exp, start_index);
    start_index+=result_l.second;

    if (start_index == exp.size() or exp[start_index] == ')' ){
        // enf of an expression, we can return it safely
        // Note: the leaf expression will increment the index to the ')' caracter
        return pair(
            result_posfix + result_l.first,
            amount_proceed + result_l.second
        );
    }

    if (start_index < exp.size() and not is_op(exp[start_index])){
        throw invalid_argument("exp start index is expected to be an operator. However, it's not: " + exp[start_index]);
    }

    if (not is_mult_op(exp[start_index])){
        return pair(
            result_posfix + result_l.first,
            amount_proceed + result_l.second
        );
    }
    amount_proceed+=result_l.second;
    result_posfix=result_l.first;
    do{

        pair result_r = pot(exp, start_index+1);
        result_posfix+=result_r.first + exp[start_index];
        start_index+=result_r.second;
        amount_proceed+=result_r.second+1; // adding 1 because of the operand
        start_index++;
    } while (is_mult_op(exp[start_index]) and exp[start_index] != ')' and start_index < exp.size());

    return pair(result_posfix, amount_proceed);
}


pair<string, int> pot(const string& exp, int start_index){

    string result_posfix = "";
    int amount_proceed = 0;

    pair result_l = leaf(exp, start_index);
    start_index+=result_l.second;

    if (start_index == exp.size() or exp[start_index] == ')' ){
        // enf of an expression, we can return it safely
        // Note: the leaf expression will increment the index to the ')' caracter
        return pair(
            result_posfix + result_l.first,
            amount_proceed + result_l.second
        );
    }

    if (start_index < exp.size() and not is_op(exp[start_index])){
        throw invalid_argument("exp start index is expected to be an operator. However, it's not: " + exp[start_index]);
    }

    if (exp[start_index] != '^'){
        return pair(
            result_posfix + result_l.first,
            amount_proceed + result_l.second
        );
    }
    amount_proceed+=result_l.second;
    result_posfix=result_l.first;
    do{

        pair result_r = leaf(exp, start_index+1);
        result_posfix+=result_r.first + exp[start_index];
        start_index+=result_r.second;
        amount_proceed+=result_r.second+1; // adding 1 because of the operand
        start_index++;
    } while (exp[start_index] == '^' and exp[start_index] != ')' and start_index < exp.size());

    return pair(result_posfix, amount_proceed);
}


pair<string, int> leaf(const string& exp, int start_index){

    if (exp[start_index] == '('){
        pair nested_r = sum(exp, start_index+1);
        assert(exp[start_index + nested_r.second+1] == ')'); // it should be start_index+nested_r.second + 1 because
        // we could be parsing a parentes not in the start of the string, example, we could be parsing right now
        // (2*c) in the exp a+c-(2*c)
        return pair(nested_r.first, nested_r.second+2);
    }

    if (is_op(exp[start_index])){
        throw invalid_argument("exp start index is not an operand: " + exp[start_index]);
    }
    return pair(string(1, exp[start_index]), 1);
}


string convert(const string& exp){
    return sum(exp, 0).first;
    
}


string trim(const string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), [](unsigned char c) {
        return std::isspace(c);
    });

    auto end = std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c) {
        return std::isspace(c);
    }).base();

    return (start < end) ? std::string(start, end) : "";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int quantity;
    string exp;

    cin>>quantity;
    cin.ignore();
    for(int i = 0; i<quantity;i++){

        getline(cin, exp);
        exp = trim(exp);
        cout<<convert(exp);
        cout<<endl;
    }


    cout.flush();

}