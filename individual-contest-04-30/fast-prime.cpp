#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    

    

    int quant_inputs;
    int current;

    auto is_prime = [](int number){
        for(int i = 2; i*i<=number; i--){
            if (number%i==0) return false;
        }
        return true;
    };
    cin>>quant_inputs;

    for(int i = 0; i< quant_inputs; i++){
        cin>>current;
        if (current != 2 and  current %2 == 0){
            cout<<"Not Prime\n";
            continue;
        }
        cout<<(is_prime(current)?"Prime\n":"Not Prime\n");
    }

}