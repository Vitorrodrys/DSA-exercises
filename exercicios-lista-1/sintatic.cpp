/**
 *   beecrowd | 1083 
 *  LEXSIM - Sintatic and Lexical Avaliator
 */
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <bits/stdc++.h>
#include <iostream>

/*
EXP = OR
OR =
    AND
    AND | AND OR
AND =
    REL
    REL . REL AND
REL =
    SUM
    SUM OPREL SUM REL
SUM =
    MULT
    MULT + MULT SUM
    MULT / MULT SUM
MULT =
    POT
    POT * POT MULT
    POT / POT MULT
POT =
    LEAF ^ LEAF
    LEAF
LEAF = 
    Tk
    number
    (exp)

OPREL =
    >
    <
    =
    #
*/


using namespace std;

bool is_op(char v){
    return (
        v == '+' or v == '-' or
        v == '*' or v == '/' or
        v == '<' or v == '>' or v == '=' or v == '#' or
        v == '.' or v == '|' or
        v == '^'
    );
}

bool is_token(char v){
    return isalnum(v);
}

bool is_valid(char v){
    return is_token(v) or is_op(v) or v=='(' or v==')';
}


enum EnumOp {
    none, lex, sint
};




class Sintatic  {

    private:
        int idx=0;

        pair<string, EnumOp> exp(const string& input){
            pair result = or_rule(input);
            if (result.second != EnumOp::none) return result;
            //if (input[idx] != ')' and input.size() > idx){
            //    return pair("", EnumOp::sint);
            //}
            return pair(result.first, EnumOp::none);
        }

        pair<string, EnumOp> or_rule(const string& input){
            pair lresult = and_rule(input);
            if (lresult.second != EnumOp::none) return lresult;

            string postfix = lresult.first;
            while(input[idx] == '|'){
                idx++;
                pair rresult=and_rule(input);
                if (rresult.second != EnumOp::none) return rresult;

                postfix+=rresult.first + "|";
            }
            return pair(postfix, EnumOp::none);
        }

        pair<string, EnumOp> and_rule(const string& input){
            pair lresult = rel_rule(input);
            if (lresult.second != EnumOp::none) return lresult;

            string postfix = lresult.first;

            while(input[idx] == '.'){
                idx++;
                pair rresult = rel_rule(input);
                if ( rresult.second != EnumOp::none) return rresult;

                postfix+=rresult.first+".";
            }
            return pair(postfix, EnumOp::none);
        }

        pair<string, EnumOp> rel_rule(const string& input){
            pair<string, EnumOp> lresult = sum(input);
            if (lresult.second != EnumOp::none) return lresult;

            string postfix = lresult.first;
            auto is_rel_op = [](char v){
                return (
                    v == '>' or v == '<' or
                    v == '=' or v == '#'
                );
            };

            char op=input[idx];
            while(is_rel_op(op)){
                idx++;
                pair rresult=sum(input);
                if (rresult.second != EnumOp::none) return rresult;
                
                postfix+= rresult.first + string(1, op);
                op=input[idx];
            }
            return pair(postfix, EnumOp::none);
        }

        pair<string, EnumOp> sum(const string& input){
            pair lresult = mult(input);
            if (lresult.second != EnumOp::none) return lresult;
        
            string postfix = lresult.first;

            char op=input[idx];
            while (op == '+' or op == '-'){
                idx++;
                pair rresult = mult(input);
                if (rresult.second != EnumOp::none) return rresult;

                postfix += rresult.first + string(1, op);
                op=input[idx];
            }
            return pair(postfix, EnumOp::none);
        }

        pair<string, EnumOp> mult(const string& input){
            pair lresult=pot(input);
            if (lresult.second != EnumOp::none) return lresult;

            string postfix=lresult.first;

            char op=input[idx];
            while (op == '/' or op == '*'){
                idx++;
                pair rresult = pot(input);
                if (rresult.second != EnumOp::none) return rresult;

                postfix += rresult.first + string(1, op);
                op=input[idx];
            }
            return pair(postfix, EnumOp::none);
        }

        pair<string, EnumOp> pot(const string& input){
            pair lresult=leaf(input);
            if (lresult.second != EnumOp::none) return lresult;

            string postfix = lresult.first;

            char op=input[idx];
            while (op == '^'){
                idx++;
                pair rresult = leaf(input);
                if (rresult.second != EnumOp::none) return rresult;

                postfix += rresult.first + string(1, op);
                op=input[idx];
            }
            return pair(postfix, EnumOp::none);
        }
        

        

        
        pair<string, EnumOp> leaf(const string& input){
            if (input.size() <= idx){
                return pair("", EnumOp::sint);
            }
            if (!is_valid(input[idx])){
                return pair("", EnumOp::lex);
            }
            if (is_op(input[idx])){
                return pair("", EnumOp::sint);
            }

            if (input[idx] == '('){
                idx++;
                auto sub_exp = exp(input);
                if (sub_exp.second != EnumOp::none) return sub_exp;
                if (input[idx] != ')') return pair("", EnumOp::sint);
                idx++;
                return sub_exp;
            }
            idx++;
            return pair(string(1,  input[idx-1]), EnumOp::none);
        }
    public:

        pair<string, EnumOp> to_postfix(const string& input){
            idx=0;
            pair result = exp(input);
            if (result.second != EnumOp::lex and idx < input.size()){
                return pair("", EnumOp::sint);
            }
            return result;
        }
};


string trim(const string& s){
    auto start = find_if_not(s.begin(), s.end(), [](char v){
        return isspace(v);
    });
    auto end = find_if_not(s.rbegin(), s.rend(), [](char v){
        return isspace(v);
    }).base();
    return (start < end)?string(start, end):"";
}


int main(){

    string exp;

    auto parser = Sintatic();
    while(getline(cin, exp)){
        exp=trim(exp);
        pair result = parser.to_postfix(exp);

        switch (result.second)
        {
        case EnumOp::none:
            cout<<result.first<<endl;
            break;
        case EnumOp::lex:
            cout<<"Lexical Error!\n";
            break;
        case EnumOp::sint:
            cout<<"Syntax Error!\n";
            break;
        }
    }
}

