#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>, greater<pair<int, int>>>
            pq;
        vector<int> vis(V, 0);
        //{weight, node}
        pq.push({0, 0});
        int sum = 0;
        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node] == 1)
                continue;
            // add it to the last
            vis[node] = 1;
            sum += wt;
            for (auto it : adj[node])
            {
                int adjNode = it[0];
                int edWt = it[1];
                if (!vis[adjNode])
                {
                    pq.push({edWt, adjNode});
                }
            }
        }
        return sum;
    }
};
int main()
{
    int V = 5;
    vector<vector<int>> edges;
    int edge;

    cout << "Enter the number of edges: ";
    cin >> edge;

    cout << "Enter the edges (node1 node2 weight):" << endl;
    for (int i = 0; i < edge; i++)
    {
        cout << "Enter the edges (node1 node2 weight):  " <<i<< endl;
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        edges.push_back({node1, node2, weight});
    }

    // Print the 2D vector
    cout << "Edges entered:" << endl;
    for (const auto &edge : edges)
    {
        for (int val : edge)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<vector<int>> adj[V];
    for (auto it : edges)
    {
        vector<int> tmp(2);
        tmp[0] = it[1];
        tmp[1] = it[2];
        adj[it[0]].push_back(tmp);

        tmp[0] = it[0];
        tmp[1] = it[2];
        adj[it[1]].push_back(tmp);
    }

    Solution obj;
    int sum = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << sum << endl;
    return 0;
}
