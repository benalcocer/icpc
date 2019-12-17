/// @author Benjamin Alcocer
/// @version 2019-12-16
/// Source: Depth-first-search from geeksforgeeks.org

#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

int dfs(int s, const vector<list<int>>& adjList);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<list<int>> graph;
    list<int> vertex;
    int t, n, r;
    int x, y;

    cin >> t;
    for (int i = 0; i < t; i++)
    {
        if (i != 0)
        {
            cout << '\n';
        }

        cin >> n >> r;
        for (int j = 0; j < n; j++)
        {
            vertex.push_back(j);
            graph.push_back(vertex);
            vertex.clear();
        }

        for (int j = 0; j < r; j++)
        {
            cin >> x >> y;
            graph[x].push_back(y);
        }

        bool pokemon = true;
        int count;
        for (int k = 0; k < n; k++)
        {
            count = dfs(k, graph);
            if (count != n)
            {
                pokemon = false;
                break;
            }
        }

        if (pokemon)
        {
            cout << "Gotta Catch Them All!";
        }
        else
        {
            cout << "Oh, oh!";
        }

        graph.clear();
    }

    return 0;
}

/// Iterative DFS
int dfs(int s, const vector<list<int>>& adjList)
{ 
    // Initially mark all verices as not visited 
    vector<bool> visited(adjList.size(), false); 
    int count = 0;
  
    // Create a stack for DFS 
    stack<int> stack; 
  
    // Push the current source node. 
    stack.push(s); 
  
    while (!stack.empty()) 
    { 
        // Pop a vertex from stack and print it
        s = stack.top();
        stack.pop();

        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited. 
        if (!visited[s]) 
        {
            count++;
            visited[s] = true;
        }

        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack. 
        for (auto i = adjList[s].begin(); i != adjList[s].end(); ++i)
            if (!visited[*i])
                stack.push(*i);
    }
    return count;
}
