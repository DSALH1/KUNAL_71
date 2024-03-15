#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int d)
    {
        data = d;
        next = NULL;
    }
};

void dfs(int v, vector<bool> &visited, Node *a[])
{
    visited[v] = true;
    cout << v << "  ";

    Node *t = a[v]->next;
    while (t->next)
    {
        if (!visited[t->data])
            dfs(t->data, visited, a);
        t = t->next;
    }
}

void bfs(int v, Node *a[], int n)
{
    vector<bool> visited(n, false);
    queue<int> q;
    visited[v] = true;
    q.push(v);

    while (!q.empty())
    {
        v = q.front();
        q.pop();
        cout << v << "  ";

        Node *t = a[v]->next;
        while (t->next)
        {
            if (!visited[t->data])
            {
                visited[t->data] = true;
                q.push(t->data);
            }
            t = t->next;
        }
    }
}

void printadj(Node *a[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        Node *temp = a[i]->next;
        cout << i << "-->";
        while (temp)
        {
            cout << temp->data << "  ";
            temp = temp->next;
        }
        cout << endl;
    }
}

void adjList(Node *a[], int n)
{
    for (int i = 0; i <= n; i++)
        a[i] = new Node(-1);

    for (int i = 1; i <= n; i++)
    {
        Node *head = a[i];
        cout << "\nEnter nodes joined with " << i << "=\n";
        int data;
        do
        {
            cout << "Enter data=";
            cin >> data;
            head->next = new Node(data);
            head = head->next;
        } while (data != -1);
    }

    printadj(a, n);
}

int main()
{
    int n;
    cout << "Enter number of nodes=";
    cin >> n;
    Node *a[n + 1];
    adjList(a, n);

    vector<bool> visited(n + 1, false);
    dfs(1, visited, a);
    cout << endl;
    bfs(1, a, n);
    return 0;
}