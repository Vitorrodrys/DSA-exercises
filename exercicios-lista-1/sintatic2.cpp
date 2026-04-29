#include <bits/stdc++.h>
using namespace std;

enum EnumOp { none, lex, sint };

bool is_op(char v){
    return (
        v == '+' || v == '-' ||
        v == '*' || v == '/' ||
        v == '<' || v == '>' || v == '=' || v == '#' ||
        v == '.' || v == '|' ||
        v == '^'
    );
}

bool is_token(char v){
    return isalnum(v);
}

bool is_valid(char v){
    return is_token(v) || is_op(v) || v=='(' || v==')';
}

int prec(char op){
    if (op == '|') return 1;
    if (op == '.') return 2;
    if (op == '>' || op == '<' || op == '=' || op == '#') return 3;
    if (op == '+' || op == '-') return 4;
    if (op == '*' || op == '/') return 5;
    if (op == '^') return 6;
    return 0;
}

// right associativity only for '^'
bool right_assoc(char op){
    return op == '^';
}

pair<string, EnumOp> to_postfix(const string& input){

    stack<char> st;
    string output;

    bool expectOperand = true;

    for (int i = 0; i < (int)input.size(); i++){
        char c = input[i];

        // --- LEXICAL ---
        if (!is_valid(c)){
            return {"", EnumOp::lex};
        }

        // --- OPERAND ---
        if (isalnum(c)){
            if (!expectOperand) return {"", EnumOp::sint};
            output += c;
            expectOperand = false;
        }

        // --- '(' ---
        else if (c == '('){
            if (!expectOperand) return {"", EnumOp::sint};
            st.push(c);
        }

        // --- ')' ---
        else if (c == ')'){
            if (expectOperand) return {"", EnumOp::sint};

            bool found = false;
            while (!st.empty()){
                if (st.top() == '('){
                    found = true;
                    st.pop();
                    break;
                }
                output += st.top();
                st.pop();
            }
            if (!found) return {"", EnumOp::sint};

            expectOperand = false;
        }

        // --- OPERATOR ---
        else {
            if (expectOperand) return {"", EnumOp::sint};

            while (!st.empty() && st.top() != '('){
                char top = st.top();

                if (
                    (right_assoc(c) && prec(top) > prec(c)) ||
                    (!right_assoc(c) && prec(top) >= prec(c))
                ){
                    output += top;
                    st.pop();
                } else break;
            }

            st.push(c);
            expectOperand = true;
        }
    }

    // --- FINAL CHECK ---
    if (expectOperand) return {"", EnumOp::sint};

    while (!st.empty()){
        if (st.top() == '(') return {"", EnumOp::sint};
        output += st.top();
        st.pop();
    }

    return {output, EnumOp::none};
}

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

    while(getline(cin, exp)){
        exp = trim(exp);

        auto result = to_postfix(exp);

        switch (result.second)
        {
        case EnumOp::none:
            cout << result.first << endl;
            break;
        case EnumOp::lex:
            cout << "Lexical Error!\n";
            break;
        case EnumOp::sint:
            cout << "Syntax Error!\n";
            break;
        }
    }
}