#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <functional>
#include <cstdio>

using namespace std;

const int MAXN = 100005;

int n;
struct Node {
    int left, right, parent;
};
vector<Node> tree(MAXN);
vector<vector<int>> adj(MAXN);
vector<bool> is_candidate(MAXN, false);
vector<int> candidates;
vector<int> subtree_size(MAXN, 0);

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
        }
        if (tree[i].right) {
            adj[i].push_back(tree[i].right);
        }
        if (tree[i].parent) {
            adj[i].push_back(tree[i].parent);
        }
    }
}

void dfs_subtree_size(int u, int p) {
    subtree_size[u] = is_candidate[u] ? 1 : 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree_size(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }
}

void collect_branch_nodes(int u, int parent, vector<int>& result) {
    if (!is_candidate[u]) return;
    result.push_back(u);
    for (int v : adj[u]) {
        if (v != parent) {
            collect_branch_nodes(v, u, result);
        }
    }
}

int find_centroid() {
    if (candidates.empty()) return -1;
    if (candidates.size() == 1) return candidates[0];
    
    int root = candidates[0];
    dfs_subtree_size(root, -1);
    
    int total_size = candidates.size();
    int best_centroid = root;
    int min_max_component = total_size + 1;
    
    for (int u : candidates) {
        int max_component = 0;
        
        for (int v : adj[u]) {
            int comp_size;
            if (v == tree[u].parent) {
                comp_size = total_size - subtree_size[u];
            } else {
                comp_size = subtree_size[v];
            }
            if (comp_size > 0) {
                max_component = max(max_component, comp_size);
            }
        }
        
        if (max_component < min_max_component) {
            min_max_component = max_component;
            best_centroid = u;
        }
    }
    
    return best_centroid;
}

vector<int> get_branches(int centroid) { 
    vector<int> branches;
    int total_size = candidates.size();
    
    for (int v : adj[centroid]) {
        if (v == tree[centroid].parent) {
            if (subtree_size[centroid] < total_size) {
                branches.push_back(v);
            }
        } else {
            if (subtree_size[v] > 0) {
                branches.push_back(v);
            }
        }
    }
    return branches;
}

void solve() {
    while (candidates.size() > 1) {
        int cand_size = candidates.size();
        
        if (cand_size == 2) {
            int a = candidates[0], b = candidates[1];
            int res = ask(a, b);
            if (res == 0 || res == 1) {
                candidates = {a};
            } else {
                candidates = {b};
            }
            break;
        }
        
        int centroid = find_centroid();
        
        dfs_subtree_size(centroid, -1);
        vector<int> branches = get_branches(centroid);
        
        vector<vector<int>> branch_nodes(branches.size());
        for (int i = 0; i < branches.size(); i++) {
            collect_branch_nodes(branches[i], centroid, branch_nodes[i]);
        }
        
        if (branches.empty()) {
            candidates = {centroid};
            continue;
        }
        
        if (branches.size() == 1) {
            int res = ask(centroid, branches[0]);
            vector<int> new_candidates;
            
            if (res == 0) {
                new_candidates.push_back(centroid);
                vector<bool> in_branch(MAXN, false);
                for (int x : branch_nodes[0]) in_branch[x] = true;
                
                for (int node : candidates) {
                    if (node != centroid && !in_branch[node]) {
                        new_candidates.push_back(node);
                    }
                }
            } else {
                new_candidates = branch_nodes[0];
            }
            
            for (int node : candidates) is_candidate[node] = false;
            candidates = new_candidates;
            for (int node : candidates) is_candidate[node] = true;
            
        } else {
            vector<pair<int, int>> branch_sizes;
            for (int i = 0; i < branches.size(); i++) {
                branch_sizes.push_back({branch_nodes[i].size(), i});
            }
            sort(branch_sizes.rbegin(), branch_sizes.rend());
            
            int idx1 = branch_sizes[0].second;
            int idx2 = branch_sizes.size() > 1 ? branch_sizes[1].second : idx1;
            int branch1 = branches[idx1];
            int branch2 = branches[idx2];
            
            int res = ask(branch1, branch2);
            vector<int> new_candidates;
            
            if (res == 0) {
                new_candidates = branch_nodes[idx1];
            } else if (res == 2) {
                new_candidates = branch_nodes[idx2];
            } else {
                new_candidates.push_back(centroid);
                vector<bool> exclude_branches(MAXN, false);
                for (int x : branch_nodes[idx1]) exclude_branches[x] = true;
                for (int x : branch_nodes[idx2]) exclude_branches[x] = true;
                
                for (int node : candidates) {
                    if (node != centroid && !exclude_branches[node]) {
                        new_candidates.push_back(node);
                    }
                }
            }
            
            for (int node : candidates) is_candidate[node] = false;
            candidates = new_candidates;
            for (int node : candidates) is_candidate[node] = true;
        }
    }
    
    printf("! %d\n", candidates[0]);
    fflush(stdout);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            tree[i].left = tree[i].right = tree[i].parent = 0;
        }
        
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &tree[i].left, &tree[i].right);
            if (tree[i].left) tree[tree[i].left].parent = i;
            if (tree[i].right) tree[tree[i].right].parent = i;
        }
        
        build_adj();
        
        candidates.clear();
        fill(is_candidate.begin(), is_candidate.end(), false);
        for (int i = 1; i <= n; i++) {
            candidates.push_back(i);
            is_candidate[i] = true;
        }
        
        solve();
    }
    
    return 0;
}