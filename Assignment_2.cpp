#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int key;
    Node *left;
    Node *right;
    string meaning;
    Node(int key, string meaning)
    {
        this->key = key;
        this->left = NULL;
        this->right = NULL;
        this->meaning = meaning;
    }
};

class BST
{
public:
    int cnt = 0;
    vector<int> v;
    vector<int> d;
    Node *root = NULL;

    Node *insert(Node *root, int k, string m)
    {
        Node *new_node = new Node(k, m);
        if (root == NULL)
        {
            return new_node;
        }
        if ((root->key) > new_node->key)
        {
            root->left = insert(root->left, k, m);
        }
        else if ((root->key) < new_node->key)
        {
            root->right = insert(root->right, k, m);
        }
        return root;
    }

    void inorder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder(root->left);
        v.push_back(root->key);
        inorder(root->right);
    }

    void delorder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        delorder(root->left);
        d.push_back(root->key);
        delorder(root->right);
    }

    Node *search(Node *root, int k)
    {
        Node *curr = root;
        while (curr->key != k)
        {
            cnt++;
            if (curr != NULL)
            {
                if (curr->key > k)
                {
                    curr = curr->left;
                }
                else
                {
                    curr = curr->right;
                }
                if (curr == NULL)
                {
                    return NULL;
                }
            }
        }
        return curr;
    }

    Node *getSuccesor(Node *curr)
    {
        curr = curr->right;
        while (curr != NULL && curr->left != NULL)
            curr = curr->left;
        return curr;
    }

    Node *deletion(Node *root, int k)
    {
        if (root == NULL)
        {
            return NULL;
        }
        if (root->key > k)
        {
            root->left = deletion(root->left, k);
            return root;
        }
        else if (root->key < k)
        {
            root->right = deletion(root->right, k);
            return root;
        }
        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            Node *succ = getSuccesor(root);
            root->key = succ->key;
            root->right = deletion(root->right, succ->key);
        }
        return root;
    }
};

int main()
{
    BST B;
    while (true)
    {
        cout << "Enter the 1 for insertion" << endl;
        int n;
        cin >> n;
        if (n == 1)
        {
            int k;
            cout << "Enter the key: " << endl;
            cin >> k;
            string m;
            cout << "Enter the meaning: " << endl;
            cin >> m;
            B.root = B.insert(B.root, k, m);
        }
        else
        {
            cout << "Inorder Traversal of Binary Search Tree is : " << endl;
            B.inorder(B.root);
            int n = B.v.size();
            for (int i = 0; i < n; i++)
            {
                cout << B.v[i] << " ";
            }
            cout << endl;
            cout << "Decreasing order of Binary Search Tree is : " << endl;
            for (int i = n - 1; i >= 0; i--)
            {
                cout << B.v[i] << " ";
            }
            cout << endl;
            cout << "Searching element-" << endl;
            int ele;
            cout << "Enter the number: " << endl;
            cin >> ele;
            if (B.search(B.root, ele) == NULL)
            {
                cout << ele << "not found !!" << B.cnt << endl;
            }
            else
            {
                cout << ele << "found!!" << B.cnt << endl;
            }
            cout << endl;
            cout << "Delete element-" << endl;
            int x;
            cout << "Enter the number: " << endl;
            cin >> x;
            B.deletion(B.root, x);
            B.delorder(B.root);
            int n1 = B.d.size();
            for (int i = 0; i < n1; i++)
            {
                cout << B.d[i] << " ";
            }
            cout << endl;
            break;
        }
    }
    return 0;
}
