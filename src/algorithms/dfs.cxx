#include <stdexcept>
#include <vector>

#include <algorithms/dfs.h>

using namespace std;


vector<vector<unsigned>> dfs(const vector<vector<unsigned>>& g, const unsigned source)
{
    const auto n = unsigned(g.size());
    if (source >= n)
        throw invalid_argument{"invalid source node ID for DFS"};
    vector<vector<unsigned>> tree(n);
    vector<unsigned> next_neighbor(n, 0);  // next_neighbor[v] == 0 => v is unvisited
    vector<unsigned> stack{source};
    stack.reserve(n);
    while (not stack.empty()) {
        const auto parent = stack.back();
        const auto& neighbors = g[parent];
        auto& child_idx = next_neighbor[parent];
        while (child_idx != neighbors.size() and next_neighbor[neighbors[child_idx]] != 0)
            ++child_idx;
        if (child_idx == neighbors.size()) {
            stack.pop_back();
            continue;
        }
        const auto child = neighbors[child_idx];
        ++child_idx;
        stack.push_back(child);
        tree[parent].push_back(child);
        tree[child].push_back(parent);
    }
    return tree;
}

bool is_connected(const vector<vector<unsigned>>& g)
{
    const auto n = unsigned(g.size());
    vector<unsigned> next_neighbor(n, 0);  // next_neighbor[v] == 0 => v is unvisited
    vector<unsigned> stack{0};
    stack.reserve(n);
    while (not stack.empty()) {
        const auto parent = stack.back();
        const auto& neighbors = g[parent];
        auto& child_idx = next_neighbor[parent];
        while (child_idx != neighbors.size() and next_neighbor[neighbors[child_idx]] != 0)
            ++child_idx;
        if (child_idx == neighbors.size()) {
            stack.pop_back();
            continue;
        }
        const auto child = neighbors[child_idx];
        ++child_idx;
        stack.push_back(child);
    }
    for (unsigned v{0}; v < n; ++v) {
        if (g[v].size() != next_neighbor[v])
            return false;
    }
    return true;
}
