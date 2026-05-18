#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int MOD = 1e9 + 7; // número primo grande



class UnionFind {

    public:
        vector<int> parent;
        vector<int> rank;


        explicit UnionFind(int elements) : 
            parent(elements), rank(elements, 1)
        {
            iota(all(parent), 0);

        }

        int find(int e){
            if (parent[e] == e){
                return e;
            }
            return parent[e] = find(parent[e]);
        }
        void union_elements(int e1, int e2){

            int find_e1 = find(e1);
            int find_e2 = find(e2);
            parent[find_e2] = find_e1;


        }



};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int people, remaining_friendship;


    cin>>people>>remaining_friendship;

    vector<int> ownes_vec(people, 0);
    for(int i = 0; i<people; i++){
        cin>>ownes_vec[i];
    }

    int from, to;
    UnionFind uf(people);

    for(int i=0; i<remaining_friendship; i++){
        cin>>from>>to;
        uf.union_elements(from, to);
        uf.union_elements(to, from);
    }


    for(auto it = uf.parent.begin(); it!=uf.parent.end(); it++){

        auto temp_it=it;
        while (temp_it-uf.parent.begin() != *temp_it){
            ownes_vec[*temp_it] += ownes_vec[temp_it-uf.parent.begin()];
            ownes_vec[temp_it-uf.parent.begin()]=0;

            temp_it=uf.parent.begin() + *temp_it;

        }

    }
    if ( 
        all_of(all(ownes_vec), [](auto v){
            return v>=0;
        })
    ){
        cout<<"POSSIBLE\n";
    }else{
        cout<<"IMPOSSIBLE\n";
    }
    return 0;
}