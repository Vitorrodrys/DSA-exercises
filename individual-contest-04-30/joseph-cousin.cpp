#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <math.h>
#include <numeric>

using namespace std;


int is_prime(int number){
    for(int i = sqrt(number); i>=2; i--){
        if (number%i==0) return false;
    }
    return true;
};

int next_prime(int current){

    current++;
    while(!is_prime(current)) current++;

    return current;
}


int main(int argc, char const *argv[])
{

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int vec_size;


    cin>>vec_size;
    while (vec_size){
        list<int> l(vec_size);
        iota(l.begin(), l.end(), 1);

        int index_to_kill=0;
        int step=2;
        while (l.size() > 1){

            index_to_kill=(index_to_kill+step-1)%l.size();
            l.erase(next(l.begin(), index_to_kill));
            step = next_prime(step);
        }
        cin>>vec_size;
        cout<<l.front()<<"\n";
    }

}
