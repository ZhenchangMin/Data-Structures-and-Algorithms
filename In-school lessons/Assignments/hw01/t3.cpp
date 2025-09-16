#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct node{
    int value;
    int index;
} Node;

void execute(vector<Node>& nodes, int quiry){
    
}
void print(vector<Node>& nodes){
    for(int i = 1; nodes[i] ; i++){
        cout << nodes[i].value << " ";
    }
    cout << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vector<Node> nodes(n+1);
        for(int i = 1; i <= n; i++){
            cin >> nodes[i].value;
            nodes[i].index = i;
        }
        while(q--){
            int quiry;
            cin >> quiry;
            execute(nodes, quiry);
        }
        print(nodes);
    }
}