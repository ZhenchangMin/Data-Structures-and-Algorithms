#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
vector<int> direct = {0, 1, 2, 3};//UP DOWN LEFT RIGHT

struct Node{
    char operand = '.';
    Node *left;
    Node *right;
    Node *parent;
};

void parseIntoTree(Node *root, ll root_i, ll root_j, vector<vector<char>> tree, int directionFrom){
    vector<int> direction = {-1, 1};
    ll cur_i = 0, cur_j = 0;
    ll last_direction;
    if (root->operand == 'P'){
        while (tree[cur_i][cur_j] == '#'){
            for (int i = 0; i < 2; i++){
                if (cur_j+direction[i] < tree[0].size() && tree[cur_i][cur_j+direction[i]] == '#'){
                    cur_j = cur_j+direction[i];
                    last_direction = i;
                    continue;
                }
                if (cur_i+direction[i] < tree.size() && tree[cur_i+direction[i]][cur_j] == '#'){
                    cur_i = cur_i+direction[i];
                    last_direction = 2 + i;
                    continue;
                }
            }
        }
        char operand;
        switch(last_direction){
            case 0:{
                if (cur_i - 1 >= 0 && tree[cur_i - 1][cur_j] != '.'){
                    operand = tree[cur_i - 1][cur_j];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_j - 1 >= 0 && tree[cur_i][cur_j - 1] != '.'){
                    operand = tree[cur_i][cur_j - 1];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_j + 1 < tree[0].size() && tree[cur_i][cur_j + 1] != '.'){
                    operand = tree[cur_i][cur_j + 1];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                break;
            }
            case 1:{
                
                if (cur_i + 1 < tree.size() && tree[cur_i + 1][cur_j] != '.'){
                    operand = tree[cur_i + 1][cur_j];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_j - 1 >= 0 && tree[cur_i][cur_j - 1] != '.'){
                    operand = tree[cur_i][cur_j - 1];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_j + 1 < tree[0].size() && tree[cur_i][cur_j + 1] != '.'){
                    operand = tree[cur_i][cur_j + 1];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                break;
            }
            case 2:{
                if (cur_i - 1 >= 0 && tree[cur_i - 1][cur_j] != '.'){
                    operand = tree[cur_i - 1][cur_j];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_i + 1 < tree.size() && tree[cur_i + 1][cur_j] != '.'){
                    operand = tree[cur_i + 1][cur_j];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_j - 1 >= 0 && tree[cur_i][cur_j - 1] != '.'){
                    operand = tree[cur_i][cur_j - 1];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }

                break;
            }
            case 3:{
                if (cur_i - 1 >= 0 && tree[cur_i - 1][cur_j] != '.'){
                    operand = tree[cur_i - 1][cur_j];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_i + 1 < tree.size() && tree[cur_i + 1][cur_j] != '.'){
                    operand = tree[cur_i + 1][cur_j];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                if (cur_j + 1 < tree[0].size() && tree[cur_i][cur_j + 1] != '.'){
                    operand = tree[cur_i][cur_j + 1];
                    Node * child = new Node();
                    child->operand = operand;
                    root->left = child;
                }
                break;
            }

        }
    }
    else{
        return;
    }


}

ll calculateTree(Node *root){
    if (!root) return 0;
    if (root->operand == 'P') return calculateTree(root->left);
    if (root->left == nullptr && root->right == nullptr) return root->operand - '0';
    if (root->operand == '+'){
        ll left = calculateTree(root->left);
        ll right = calculateTree(root->right);
        return left + right;
    }
    if (root->operand == '-'){
        ll left = calculateTree(root->left);
        ll right = calculateTree(root->right);
        return left - right > 0 ? left - right : right - left;
    }
    if (root->operand == '*'){
        ll left = calculateTree(root->left);
        ll right = calculateTree(root->right);
        return left * right;
    }
    if (root->operand == '/'){
        ll left = calculateTree(root->left);
        ll right = calculateTree(root->right);
        ll bigger = left > right ? left : right;
        ll smaller = left <= right ? left : right;
        return bigger / smaller;
    }
    return root->operand - '0';
}

int main(){
    ios:: sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    vector<vector<char>> tree(n * m);
    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < m; j++){
            tree[i][j] = ' ';
        }
    }
    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < m; j++){
            cin >> tree[i][j];
        }
    }
    // input over

    // look for P place
    ll root_i = 0, root_j = 0;
    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < m; j++){
            if (tree[i][j] == 'P'){
                root_i = i;
                root_j = j;
                break;
            }
        }
    }
    Node *root = new Node();
    root->operand = 'P';

    parseIntoTree(root, root_i, root_j, tree, 0);
    ll ans = calculateTree(root);
    cout << ans << '\n';
    return 0;
}