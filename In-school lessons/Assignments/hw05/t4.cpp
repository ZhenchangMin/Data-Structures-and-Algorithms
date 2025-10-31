#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <cstdio>

using namespace std;

const int MAXN = 100005;

int n;
struct Node {
    int left, right, parent;
};
vector<Node> tree(MAXN);
vector<vector<int>> adj(MAXN);
unordered_set<int> candidate_set;

int ask(int u, int v) {
    printf("? %d %d\n", u, v);
    fflush(stdout);
    int res;
    scanf("%d", &res);
    return res;
}

void build_adj() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        if (tree[i].left) {
            adj[i].push_back(tree[i].left);
            tree[tree[i].left].parent = i;
        }
        if (tree[i].right) {
            adj[i].push_back(tree[i].right);
            tree[tree[i].right].parent = i;
        }
        if (tree[i].parent) {
            adj[i].push_back(tree[i].parent);
        }
    }
}

int calc_subtree_size(int u, int parent) {
    int size = 0;
    function<void(int, int)> dfs = [&](int node, int p) {
        if (candidate_set.count(node) == 0) return;
        size++;
        for (int v : adj[node]) {
            if (v != p) {
                dfs(v, node);
            }
        }
    };
    dfs(u, parent);
    return size;
}

int find_centroid(int root) {
    int total = calc_subtree_size(root, 0);
    if (total <= 1) {
        return root;
    }
    
    int centroid = -1;
    function<int(int, int)> dfs_centroid = [&](int u, int p) -> int {
        int size = 1;
        int max_subtree = 0;
        
        for (int v : adj[u]) {
            if (v == p || candidate_set.count(v) == 0) continue;
            int sub_size = dfs_centroid(v, u);
            size += sub_size;
            max_subtree = max(max_subtree, sub_size);
        }
        
        int remaining = total - size;
        if (max_subtree * 2 <= total && remaining * 2 <= total && centroid == -1) {
            centroid = u;
        }
        
        return size;
    };
    
    dfs_centroid(root, 0);
    return (centroid != -1) ? centroid : root;
}

void collect_branch_nodes_set(int u, int parent, unordered_set<int>& result_set) {
    if (candidate_set.count(u) == 0) return; 
    result_set.insert(u);
    for (int v : adj[u]) {
        if (v != parent) {
            collect_branch_nodes_set(v, u, result_set);
        }
    }
}

void solve() {
    int cand_size = candidate_set.size();
    if (cand_size == 1) {
        printf("! %d\n", *candidate_set.begin());
        fflush(stdout);
        return;
    }
    
    if (cand_size == 2) {
        vector<int> temp(candidate_set.begin(), candidate_set.end());
        int a = temp[0], b = temp[1];
        int res = ask(a, b);
        if (res == 0 || res == 1) {
            printf("! %d\n", a);
        } else {
            printf("! %d\n", b);
        }
        fflush(stdout);
        return;
    }
    
    int root = *candidate_set.begin();
    int centroid = find_centroid(root);
    
    vector<int> branches;
    for (int v : adj[centroid]) {
        if (calc_subtree_size(v, centroid) > 0) {
            branches.push_back(v);
        }
    }
    
    if (branches.size() == 1) {
        int res = ask(centroid, branches[0]);
        unordered_set<int> new_candidates;
        
        if (res == 0) {
            new_candidates.insert(centroid);
            unordered_set<int> branch_set;
            collect_branch_nodes_set(branches[0], centroid, branch_set);
            for (int node : candidate_set) {
                if (node != centroid && branch_set.count(node) == 0) {
                    new_candidates.insert(node);
                }
            }
        } else {
            collect_branch_nodes_set(branches[0], centroid, new_candidates);
        }
        
        candidate_set = move(new_candidates);
        solve();
    } else {
        vector<pair<int, int>> branch_sizes;
        for (int branch : branches) {
            int size = calc_subtree_size(branch, centroid);
            branch_sizes.push_back({size, branch});
        }
        
        sort(branch_sizes.rbegin(), branch_sizes.rend());
        
        int branch1 = branch_sizes[0].second;
        int branch2 = (branch_sizes.size() > 1) ? branch_sizes[1].second : -1;
        
        if (branch2 == -1) {
            int res = ask(centroid, branch1);
            unordered_set<int> new_candidates;
            if (res == 0) {
                new_candidates.insert(centroid);
                unordered_set<int> branch_set;
                collect_branch_nodes_set(branch1, centroid, branch_set);
                for (int node : candidate_set) {
                    if (node != centroid && branch_set.count(node) == 0) {
                        new_candidates.insert(node);
                    }
                }
            } else {
                collect_branch_nodes_set(branch1, centroid, new_candidates);
            }
            candidate_set = move(new_candidates);
            solve();
            return;
        }
        
        int res = ask(branch1, branch2);
        unordered_set<int> new_candidates;
        
        if (res == 0) {
            collect_branch_nodes_set(branch1, centroid, new_candidates);
        } else if (res == 2) {
            collect_branch_nodes_set(branch2, centroid, new_candidates);
        } else {
            new_candidates.insert(centroid);
            unordered_set<int> branch1_set, branch2_set;
            collect_branch_nodes_set(branch1, centroid, branch1_set);
            collect_branch_nodes_set(branch2, centroid, branch2_set);
            
            for (int node : candidate_set) {
                if (node != centroid && branch1_set.count(node) == 0 && branch2_set.count(node) == 0) {
                    new_candidates.insert(node);
                }
            }
        }
        
        candidate_set = move(new_candidates);
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &tree[i].left, &tree[i].right);
            tree[i].parent = 0;
            tree[tree[i].left].parent = i;
            tree[tree[i].right].parent = i;
        }
        
        build_adj();
        
        candidate_set.clear();
        for (int i = 1; i <= n; i++) {
            candidate_set.insert(i);
        }
        
        solve();
    }
    
    return 0;
}
