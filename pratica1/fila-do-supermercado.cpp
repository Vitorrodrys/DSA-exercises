#include <bits/stdc++.h>
#include <unordered_map>
#include <list>
#include <queue>
#include <set>
#include <functional> 

using namespace std;


void check_time_queue(
    int now,
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& next_time_to_release,
    priority_queue<int, vector<int>, greater<int>>& free_cashiers
){
    if (next_time_to_release.empty()){
        return;
    }
    pair top=next_time_to_release.top();
    //free_cashiers.push(top.second);
    while (top.first == now){
        next_time_to_release.pop();
        free_cashiers.push(top.second);
        top=next_time_to_release.top();
    }
}

void handle_customer(
    int now,
    int client_index,
    priority_queue<int, vector<int>, greater<int>>& free_cashiers,
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& next_time_to_release,
    int cashier_time[], int client_basket_itens[]
){
    
    int cashier_index=free_cashiers.top();
    free_cashiers.pop();
    int cashier_time_to_process=now+cashier_time[cashier_index]*client_basket_itens[client_index];
    next_time_to_release.push(pair(cashier_time_to_process, cashier_index));
}

priority_queue<int, vector<int>, greater<int>> create_queue(int itens){
    priority_queue<int, vector<int>, greater<int>> queue;
    for(int i = 0; i<itens; i++){
        queue.push(i);
    }
    return queue;
}


int solve(int cashiers, int clients, int cashier_time[], int client_basket_itens[]){

    int time=0;
    priority_queue<int, vector<int>, greater<int>> free_cashiers = create_queue(cashiers);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>> release_at;

    int client_index=0;

    do{

        do{
            handle_customer(time, client_index, free_cashiers, release_at, cashier_time, client_basket_itens);
            check_time_queue(time, release_at, free_cashiers);
            client_index++;

        }while(!free_cashiers.empty() and client_index < clients);
        time++;

        while(free_cashiers.empty() and client_index < clients){
            pair top=release_at.top();
            time=top.first;
            free_cashiers.push(top.second);

            release_at.pop();
            while( release_at.size() > 0 and release_at.top().first == time ){
                top = release_at.top();
                free_cashiers.push(top.second);
                release_at.pop();
                top = release_at.top();
            }

            handle_customer(time, client_index, free_cashiers, release_at, cashier_time, client_basket_itens);
            client_index++;
            
        }

        if (client_index == clients){
            pair top=pair(0,0);
            while(release_at.size()>0){
                top=release_at.top();
                release_at.pop();
                time=top.first;
            }
            return time;
        }

    }while (release_at.size() > 0);
    return time;
    
}


int main(){
    int cashiers, clients;

    cin>>cashiers>>clients;

    int cashier_time[cashiers] = {0};
    int client_basket_itens[clients] = {0};

    for (int i = 0; i<cashiers; i++){
        cin>>cashier_time[i];
    }

    for (int i = 0; i < clients; i++){
        cin>>client_basket_itens[i];
    }

    printf("%d\n", solve(cashiers, clients, cashier_time, client_basket_itens));


}