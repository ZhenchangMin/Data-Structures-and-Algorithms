#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

const int HASH_SIZE = 10007;

struct Node {
    ll value;
    Node* next;
    Node(ll val) : value(val), next(nullptr) {}
};

class HashSet {
private:
    vector<Node*> table;
    int size;
    
    int hash(ll x) {
        return x % HASH_SIZE;
    }
    
public:
    HashSet() : table(HASH_SIZE, nullptr), size(0) {}
    
    void insert(ll x) {
        int index = hash(x);
        Node* curr = table[index];
        
        while (curr != nullptr) {
            if (curr->value == x) {
                return;
            }
            curr = curr->next;
        }
        
        Node* newNode = new Node(x);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }
    
    bool find(ll x) {
        int index = hash(x);
        Node* curr = table[index];
        
        while (curr != nullptr) {
            if (curr->value == x) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    
    int getSize() {
        return size;
    }
};

int main(){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        
        HashSet s;
        ll found = 0;
        
        for (int i = 0; i < n; i++){
            string option;
            cin >> option;
            
            if (option == "insert"){
                ll x;
                cin >> x;
                for (int j = 1; j <= 1000; j++){
                    s.insert(x * j);
                }
            }
            else if (option == "find"){
                ll x;
                cin >> x;
                if (s.find(x)){
                    found++;
                }
            }
        }
        
        cout << s.getSize() << ' ' << found << '\n';
    }
    return 0;
}